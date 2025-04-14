/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   env_add.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: Jpaulis <Jpaulis@student.s19.be>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/12 16:20:36 by Jpaulis		   #+#	#+#			 */
/*   Updated: 2025/03/31 21:38:48 by Jpaulis		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

// Allouer de la mémoire pour le nouveau nœud
// Initialiser les champs du nouveau nœud
int	add_env_var(t_env_list **env_list, char *name, char *value)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new_node)
		return (0);
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
	ft_env_back(env_list, new_node);
	return (1);
}

char	*get_env_value(t_env_list *list, char *key)
{
	t_env_list	*current;

	current = list;
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
void	add_env_var_without_value(t_env_list **env_list, char *key)
{
	if (!get_env_value(*env_list, key))
		add_env_var(env_list, key, "");
}

void	update_env_var(t_env_list **env_list, char *name, char *value)
{
	t_env_list	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	add_env_var(env_list, name, value);
}

void	update_cmd_from_args(t_cmd *cmd)
{
	if (cmd->args && cmd->args[0])
	{
		free(cmd->cmd);
		cmd->cmd = ft_strdup(cmd->args[0]);
	}
}
