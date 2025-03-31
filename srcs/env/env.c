/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:29:44 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 22:04:32 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Ajoute une variable d'environnement à partir d'une chaîne "KEY=VALUE"
 * @param env_list Liste des variables d'environnement
 * @param var_str Chaîne au format "KEY=VALUE"
 * @return 0 en cas de succès, -1 sinon
 */
int add_env_var_from_string(t_env_list **env_list, char *var_str)
{
    char *equal_sign;
    char *key;
    char *value;
    int result;

    equal_sign = ft_strchr(var_str, '=');
    if (!equal_sign)
        return (-1);
    // Extraire la clé et la valeur
    key = ft_substr(var_str, 0, equal_sign - var_str);
    value = ft_strdup(equal_sign + 1);
    if (!key || !value)
    {
        free(key);
        free(value);
        return (-1);
    }
    // Utiliser la fonction de base
    result = add_env_var(env_list, key, value);
    free(key);
    free(value);
    return (result);
}

/**
 * Recherche une variable d'environnement par son nom
 * @param env_list Liste des variables d'environnement
 * @param key Nom de la variable à rechercher
 * @return Pointeur sur la valeur ou NULL si non trouvée
 */
char *get_env_var(t_env_list *env_list, char *key)
{
    t_env_list *current;

    current = env_list;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

/**
 * Affiche l'environnement (liste chaînée d'env_list)
 * @param env_list Le début de la liste chaînée d'environnement
 */
void print_env_list(t_env_list *env_list)
{
    t_env_list *current;

    current = env_list;
    while (current)
    {
        write(STDOUT_FILENO, current->key, strlen(current->key));
        write(STDOUT_FILENO, "=", 1);
        write(STDOUT_FILENO, current->value, strlen(current->value));
        write(STDOUT_FILENO, "\n", 1);
        current = current->next;
    }
}
