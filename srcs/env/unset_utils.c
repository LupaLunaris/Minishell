/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:58:16 by malafont          #+#    #+#             */
/*   Updated: 2025/04/04 11:58:25 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_node(t_env_list *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

/**
 * Supprime une variable d'environnement de la liste
 * @param env_list Liste des variables d'environnement
 * @param key Nom de la variable à supprimer
 */
void	delete_env_var(t_env_list **env_list, char *key)
{
	t_env_list	*current;
	t_env_list	*previous;

	if (!*env_list)
		return ;
	if (ft_strcmp((*env_list)->key, key) == 0)
	{
		current = *env_list;
		*env_list = (*env_list)->next;
		free_node(current);
		return ;
	}
	previous = *env_list;
	current = (*env_list)->next;
	while (current && ft_strcmp(current->key, key))
	{
		previous = current;
		current = current->next;
	}
	if (current)
	{
		previous->next = current->next;
		free_node(current);
	}
}
