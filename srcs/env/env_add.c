/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:20:36 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 21:36:50 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Ajoute une variable d'environnement à la liste
 * @param env_list Un pointeur vers la liste d'environnement
 * @param key La clé de la variable
 * @param value La valeur de la variable
 * @return 0 en cas de succès, -1 en cas d'erreur
 */
// int add_env_var(t_env_list **env_list, char *key, char *value)
// {
// 	t_env_list *new_node;
// 	t_env_list *current;

// 	// Créer un nouveau nœud
// 	new_node = malloc(sizeof(t_env_list));
// 	if (!new_node)
// 		return (-1);
// 	// Initialiser le nouveau nœud
// 	new_node->key = ft_strdup(key);
// 	new_node->value = ft_strdup(value);
// 	new_node->next = NULL;
// 	if (!new_node->key || !new_node->value)
// 	{
// 		free_env_list(new_node);  // Fonction pour libérer un nœud
// 		return (-1);
// 	}
// 	// Si la liste est vide, le nouveau nœud devient la tête
// 	if (*env_list == NULL)
// 	{
// 		*env_list = new_node;
// 		return (0);
// 	}
// 	// Sinon, ajouter à la fin
// 	current = *env_list;
// 	while (current->next)
// 		current = current->next;
// 	current->next = new_node;
// 	return (0);
// }

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
