/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:42:25 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/17 13:56:48 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Affiche les variables d'environnement au format de la commande export
 * (trié et avec le format "declare -x KEY="VALUE"")
 * @param env_list Liste des variables d'environnement
 */
void print_export_list(t_env_list *env_list)
{
	t_env_list **sorted_env;
	int count;
	int i;

	count = count_env_vars(env_list); // Compter les variables et les copier dans un tableau
	sorted_env = malloc(sizeof(t_env_list *) * (count + 1));
	i = 0;
	while (env_list) // Copier les pointeurs
	{
		sorted_env[i++] = env_list;
		env_list = env_list->next;
	}
	sorted_env[i] = NULL;
	sort_env_list(sorted_env, count); // Trier le tableau
	// Afficher les variables au format declare -x
	i = 0;
	while (i < count)
	{
		printf("declare -x %s", sorted_env[i]->key);
		if (sorted_env[i]->value && ft_strlen(sorted_env[i]->value) > 0)
			printf("=\"%s\"", sorted_env[i]->value);
		printf("\n");
		i++;
	}
	free(sorted_env);
}

static int process_export_with_equals(char *arg, t_env_list **env_list)
{
	char *key;
	char *value;
	int ret;
	char *equals_pos;

	equals_pos = ft_strchr(arg, '=');
	if (!equals_pos)
		return (EXIT_SUCCESS);
	// Séparer la clé et la valeur
	key = ft_substr(arg, 0, equals_pos - arg);
	value = ft_strdup(equals_pos + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (EXIT_FAILURE);
	}
	ret = add_env_var(env_list, key, value);
	free(key);
	free(value);
	return (ret);
}

/**
 * Traite un argument spécifique d'export
 * @return 0 pour succès, 1 pour erreur
 */
int process_export_arg(char *arg, t_env_list **env_list)
{
	// Si l'argument commence par un tiret, erreur
	if (arg[0] == '-')
	{
		error_handler("export", "options not supported", 0, 1);
		return (EXIT_FAILURE);
	}
	// Si l'identifiant n'est pas valide, erreur
	if (!is_valid_identifier(arg))
	{
		error_handler("export", ft_strjoin(arg, ": not a valid identifier"), 0, 1);
		return (EXIT_FAILURE);
	}
	// Avec un signe égal : ajoute/modifie la variable
	if (ft_strchr(arg, '=') != NULL)
		return (process_export_with_equals(arg, env_list));
	// Sans signe égal : crée si n'existe pas
	else if (!get_env_var(*env_list, arg))
		add_env_var_without_value(env_list, arg);
	return (EXIT_SUCCESS);
}


/**
 * Implémente la commande builtin 'export'
 */
int builtin_export(t_cmd *command, t_env_list **env_list)
{
	int i;
	int status;

	// Sans arguments : affiche les variables
	if (command->args[1] == NULL)
	{
		print_export_list(*env_list);
		return (EXIT_SUCCESS);
	}
	// Traite tous les arguments
	status = EXIT_SUCCESS;
	i = 1;
	while (command->args[i])
	{
		if (process_export_arg(command->args[i], env_list) == EXIT_FAILURE)
			status = EXIT_FAILURE;
		i++;
	}
	return (status);
}
