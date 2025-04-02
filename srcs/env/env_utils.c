/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:54:59 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/02 21:54:47 by Jpaulis          ###   ########.fr       */
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

/**
 * Compte le nombre de variables dans la liste d'environnement
 * @param env_list Liste des variables d'environnement
 * @return Nombre de variables
 */
int	count_env_vars(t_env_list *env_list)
{
	int			count;
	t_env_list	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/**
 * Trie un tableau de pointeurs vers des variables
 * d'environnement par ordre alphabétique des clés
 * @param env_array Tableau de pointeurs vers des nœuds à trier
 * @param count Nombre d'éléments dans le tableau
 */
void	sort_env_list(t_env_list **env_array, int count)
{
	int			i;
	int			j;
	t_env_list	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env_array[j]->key, env_array[j + 1]->key) > 0)
			{
				temp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

char	*ft_strjoin_env(char const *s1, char const *s2)
{
	char	*tmp;
	size_t	size;
	size_t	i;

	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	tmp = malloc(sizeof(char) * size);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '=';
	i++;
	while (i < size - 1)
	{
		tmp[i] = s2[i - ft_strlen(s1) - 1];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
