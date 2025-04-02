/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:29:44 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/02 15:22:13 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Recherche une variable d'environnement par son nom
 * @param env_list Liste des variables d'environnement
 * @param key Nom de la variable à rechercher
 * @return Pointeur sur la valeur ou NULL si non trouvée
 */
char *get_env_var(t_env_list *env_list, char *key)
{
	t_env_list *current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return current->value;
		current = current->next;
	}
	return NULL;
}

/**
 * Affiche l'environnement (liste chaînée d'env_list)
 * @param env_list Le début de la liste chaînée d'environnement
 */
void print_env_list(t_env_list *env_list)
{
	t_env_list *current;

	current = env_list;
	while (current)
	{
		write(STDOUT_FILENO, current->key, strlen(current->key));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, current->value, strlen(current->value));
		write(STDOUT_FILENO, "\n", 1);
		current = current->next;
	}
}
