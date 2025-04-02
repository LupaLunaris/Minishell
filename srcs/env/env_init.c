/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:18:45 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/02 21:54:43 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Initialise la liste d'environnement à partir du envp
 * @param envp Le tableau d'environnement fourni au programme
 * @return Un pointeur vers la liste chaînée des variables d'environnement
 */
t_env_list	*init_env(char **envp)
{
	t_env_list	*env_list;
	int			i;
	char		*key;
	char		*value;
	char		*equals_pos;

	env_list = NULL;
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		equals_pos = ft_strchr(envp[i], '=');
		if (equals_pos)
		{
			key = ft_substr(envp[i], 0, equals_pos - envp[i]);
			value = ft_strdup(equals_pos + 1);
			if (key && value)
				add_env_var(&env_list, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (env_list);
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
