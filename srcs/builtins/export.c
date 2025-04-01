/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:42:25 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 21:43:49 by Jpaulis          ###   ########.fr       */
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
    if (!sorted_env)
        return;
    i = 0;
    while (env_list) // Copier les pointeurs
    {
        sorted_env[i++] = env_list;
        env_list = env_list->next;
    }
    sorted_env[i] = NULL;
    sort_env_list(sorted_env, count);
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

/**
 * Traite une assignation de variable (comme KEY=VALUE)
 * @return 0 pour succès, 1 pour erreur
 */
static int process_export_with_equals(char *arg, t_env_list **env_list)
{
    char *key;
    char *value;
    char *equals_pos;

    // Trouver le signe =
    equals_pos = ft_strchr(arg, '=');
    if (!equals_pos)
        return (EXIT_SUCCESS);

    // Extraire la clé (avant le =)
    key = ft_substr(arg, 0, equals_pos - arg);

    // Extraire la valeur (après le =)
    value = ft_strdup(equals_pos + 1);

    if (!key || !value)
    {
        free(key);
        free(value);
        return (EXIT_FAILURE);
    }

    // Vérifier si la clé est valide
    if (!is_valid_identifier(key))
    {
        free(key);
        free(value);
        return (EXIT_FAILURE);
    }

    // Ajouter ou mettre à jour la variable
    int ret = add_env_var(env_list, key, value);

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

    // Avec un signe égal : ajoute/modifie la variable
    if (ft_strchr(arg, '=') != NULL)
        return (process_export_with_equals(arg, env_list));

    // Vérifier si l'identifiant est valide
    if (!is_valid_identifier(arg))
    {
        error_handler("export", "not a valid identifier", 0, 0);
        return (EXIT_FAILURE);
    }

    // Sans signe égal : crée si n'existe pas
    if (!get_env_var(*env_list, arg))
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
        // Vérifier s'il faut supprimer les guillemets
        char *arg = command->args[i];
        char *processed_arg = arg;

        // Vérifier si l'argument contient des guillemets
        // int has_quotes = 0;
        // for (int j = 0; arg[j]; j++) {
        //     if (arg[j] == '\'' || arg[j] == '"') {
        //         has_quotes = 1;
        //         break;
        //     }
        // }

        // Si l'argument contient des guillemets, les supprimer
        // if (has_quotes) {
        //     processed_arg = strip_quotes(arg);
        //     if (!processed_arg) {
        //         status = EXIT_FAILURE;
        //         i++;
        //         continue;
        //     }
        // }

        if (process_export_arg(processed_arg, env_list) == EXIT_FAILURE)
            status = EXIT_FAILURE;

        // Si on a créé une nouvelle chaîne, la libérer
        if (processed_arg != arg)
            free(processed_arg);

        i++;
    }

    return (status);
}