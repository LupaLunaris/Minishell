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
 * Ajoute une nouvelle variable d'environnement à la liste
 * @param env_list Liste des variables d'environnement
 * @param key Nom de la variable
 * @param value Valeur de la variable
 */
void add_env_node(t_env_list **env_list, char *key, char *value)
{
	t_env_list *new_node;
	t_env_list *current;

	new_node = (t_env_list *)malloc(sizeof(t_env_list)); // Créer un nouveau nœud
	if (!new_node)
		return; // Gestion d'erreur selon ton système
	// Copier les données
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	// Si la liste est vide, le nouveau nœud devient la tête
	if (*env_list == NULL)
	{
		*env_list = new_node;
		return;
	}
	// Sinon, ajouter à la fin de la liste
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

static void free_node(t_env_list *node)
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
void delete_env_var(t_env_list **env_list, char *key)
{
	t_env_list *current;
	t_env_list *previous;

	if (!*env_list)
		return;
	if (ft_strcmp((*env_list)->key, key) == 0)
	{
		current = *env_list;
		*env_list = (*env_list)->next;
		free_node(current);
		return;
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
int count_env_vars(t_env_list *env_list)
{
	int count;
	t_env_list *current;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return count;
}

/**
 * Trie un tableau de pointeurs vers des variables d'environnement par ordre alphabétique des clés
 * @param env_array Tableau de pointeurs vers des nœuds à trier
 * @param count Nombre d'éléments dans le tableau
 */
void sort_env_list(t_env_list **env_array, int count)
{
	int i;
	int j;
	t_env_list *temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env_array[j]->key, env_array[j + 1]->key) > 0) // Comparer les clés et échanger si nécessaire (tri à bulles)
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