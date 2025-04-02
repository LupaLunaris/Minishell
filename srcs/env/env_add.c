/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:20:36 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/02 15:32:33 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_env_var(t_env_list **env_list, char *name, char *value)
{
	t_env_list	*new_node;
	t_env_list	*current;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new_node)
		return (0);
	new_node->key = ft_strdup(name);
	if (!new_node->key)
		return (free(new_node), 0);
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		return (free(new_node->key), free(new_node), 0);
	new_node->next = NULL;
	if (*env_list == NULL)
	{
		*env_list = new_node;
		return (1);
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
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

/**
 * Ajoute une variable d'environnement à partir d'une chaîne "KEY=VALUE"
 * @param env_list Liste des variables d'environnement
 * @param var_str Chaîne au format "KEY=VALUE"
 * @return 0 en cas de succès, -1 sinon
 */
int	add_env_var_from_string(t_env_list **env_list, char *var_str)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	int		result;

	equal_sign = ft_strchr(var_str, '=');
	if (!equal_sign)
		return (-1);
	key = ft_substr(var_str, 0, equal_sign - var_str);
	value = ft_strdup(equal_sign + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (-1);
	}
	result = add_env_var(env_list, key, value);
	free(key);
	free(value);
	return (result);
}
