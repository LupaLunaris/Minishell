/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:18:45 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/12 16:20:11 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Initialise la liste d'environnement à partir du envp
 * @param envp Le tableau d'environnement fourni au programme
 * @return Un pointeur vers la liste chaînée des variables d'environnement
 */
t_env_list *init_env(char **envp)
{
    t_env_list *env_list = NULL;
    int i = 0;
    char *key;
    char *value;
    char *equals_pos;

    if (!envp)
        return (NULL);
    while (envp[i])
    {
        equals_pos = ft_strchr(envp[i], '=');
        if (equals_pos)
        {
            // Extraire la clé (avant le '=')
            key = ft_substr(envp[i], 0, equals_pos - envp[i]);
            // Extraire la valeur (après le '=')
            value = ft_strdup(equals_pos + 1);
            // Ajouter à notre liste d'environnement
            if (key && value)
                add_env_var(&env_list, key, value);
                
            // Libérer la mémoire allouée
            free(key);
            free(value);
        }
        i++;
    }
    return (env_list);
}
