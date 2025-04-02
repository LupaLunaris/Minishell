/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 23:01:06 by Jpaulis          ###   ########.fr       */
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

    count = count_env_vars(env_list);
    sorted_env = malloc(sizeof(t_env_list *) * (count + 1));
    if (!sorted_env)
        return;
    i = 0;
    while (env_list)
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
 * Vérifie si un identifiant est valide pour une variable d'environnement
 * @param id L'identifiant à vérifier
 * @return 1 si valide, 0 sinon
 */
int is_valid_identifier_exp(char *id)
{
    int i;

    if (!id || !*id)
        return (0);
        
    // Premier caractère doit être une lettre ou underscore
    if (!ft_isalpha(id[0]) && id[0] != '_')
        return (0);
        
    // Vérifie les caractères suivants
    i = 1;
    while (id[i])
    {
        // Permettre les chiffres et underscores dans le reste de l'identifiant
        if (!ft_isalnum(id[i]) && id[i] != '_')
            return (0);  // Ne pas accepter les caractères autres que alphanumériques et underscores
        i++;
    }
    
    return (1);
}

static void remove_quotes_from_value(char **value)
{
    char *new_value;
    int i, j = 0;
    int in_quotes = 0;
    char quote_type = 0;
    
    if (!*value)
        return;
    
    new_value = malloc(ft_strlen(*value) + 1);
    if (!new_value)
        return;
    
    for (i = 0; (*value)[i]; i++)
    {
        // Traiter les guillemets
        if ((*value)[i] == '"' || (*value)[i] == '\'')
        {
            if (in_quotes == 0)
            {
                in_quotes = 1;
                quote_type = (*value)[i];
            }
            else if ((*value)[i] == quote_type)
            {
                in_quotes = 0;
                quote_type = 0;
            }
            else
            {
                // C'est un guillemet différent à l'intérieur des guillemets, on le conserve
                new_value[j++] = (*value)[i];
            }
        }
        else
        {
            // Caractère normal, on le conserve
            new_value[j++] = (*value)[i];
        }
    }
    
    new_value[j] = '\0';
    free(*value);
    *value = new_value;
}


static int process_export_with_equals(char *arg, t_env_list **env_list)
{
    char *key;
    char *value;
    char *equals_pos;

    equals_pos = ft_strchr(arg, '=');
    if (!equals_pos)
        return EXIT_SUCCESS;

    // Extraire la clé et la valeur
    key = ft_substr(arg, 0, equals_pos - arg);
    value = ft_strdup(equals_pos + 1);
    
    if (!key || !value)
    {
        free(key);
        free(value);
        return EXIT_FAILURE;
    }
    
    // Vérifier la validité de la clé
    if (!is_valid_identifier(key))
    {
        ft_putstr_fd("minishell: export: `", 2);
        ft_putstr_fd(arg, 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        free(key);
        free(value);
        return EXIT_FAILURE;
    }
    
    // Enlever les guillemets de la valeur si présents
    remove_quotes_from_value(&value);
    
    // Mettre à jour la variable d'environnement
    update_env_var(env_list, key, value);
    
    free(key);
    free(value);
    return EXIT_SUCCESS;
}

/**
 * Traite un argument spécifique d'export
 * @return 0 pour succès, 1 pour erreur
 */
int process_export_arg(char *arg, t_env_list **env_list)
{
    // Si l'argument contient un signe égal
    if (ft_strchr(arg, '=') != NULL)
        return (process_export_with_equals(arg, env_list));
        
    // Sans signe égal: vérifier si l'identifiant est valide
    if (!is_valid_identifier_exp(arg))
    {
        error_handler("export", ft_strjoin(arg, ": not a valid identifier"), 0, 1);
        return (EXIT_FAILURE);
    }
    
    // Si l'identifiant est valide et n'existe pas, l'ajouter sans valeur
    if (!get_env_var(*env_list, arg))
        add_env_var(env_list, arg, "");  // Ajouter avec valeur vide
        
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
