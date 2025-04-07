/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:54:59 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/12 16:00:52 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * Trie un tableau de pointeurs vers des variables d'environnement
  par ordre alphabétique des clés
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

static t_env_list	*ft_env_last(t_env_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_env_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_env_last(*lst);
	last->next = new;
}
