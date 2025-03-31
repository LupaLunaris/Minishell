/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:20:36 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 21:38:48 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int add_env_var(t_env_list **env_list, char *name, char *value)
{
    t_env_list *new_node;
    
    // Allouer de la mémoire pour le nouveau nœud
    new_node = (t_env_list *)malloc(sizeof(t_env_list));
    if (!new_node)
        return (0); // Échec
    
    // Initialiser les champs du nouveau nœud
    new_node->key = ft_strdup(name);
    if (!new_node->key)
    {
        free(new_node);
        return (0);
    }
    
    new_node->value = ft_strdup(value);
    if (!new_node->value)
    {
        free(new_node->key);
        free(new_node);
        return (0);
    }
    
    new_node->next = NULL;
    
    // Cas particulier : liste vide
    if (*env_list == NULL)
    {
        *env_list = new_node;
        return (1); // Succès
    }
    
    // Sinon, ajouter à la fin de la liste
    t_env_list *current = *env_list;
    while (current->next)
        current = current->next;
    
    current->next = new_node;
    return (1); // Succès
}

char *get_env_value(t_env_list *list, char *key)
{
    t_env_list *current = list;

    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
            return (current->value);
        current = current->next;
    }
    return (NULL);
}

/**
 * Ajoute une variable d'environnement sans valeur si elle n'existe pas déjà
 * @param env_list Liste des variables d'environnement
 * @param key Nom de la variable à ajouter
 */
void add_env_var_without_value(t_env_list **env_list, char *key)
{
	// Si la variable n'existe pas, l'ajouter avec une valeur vide
	if (!get_env_value(*env_list, key))
		add_env_var(env_list, key, "");
}
