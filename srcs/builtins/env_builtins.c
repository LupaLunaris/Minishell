/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:22:25 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/16 22:03:49 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Implémente la commande builtin 'env' qui affiche l'environnement
 * @param command La structure de commande contenant les arguments
 * @param env_list Pointeur vers le début de la liste chaînée d'environnement
 * @return Exit status de la commande (0 pour succès, autre pour erreur)
 */
int builtin_env(t_cmd *cmd, t_env_list **env_list)
{
	// Vérifie qu'aucun argument n'est fourni
	if (cmd->args[1] != NULL)
		return error_handler("env", "too many arguments", 0, EXIT_FAILURE);
	// Vérifie que la liste d'environnement existe
	if (!env_list)
		return error_handler("env", "environment not available", 0, EXIT_FAILURE);
	// Affiche l'environnement
	print_env_list(*env_list);
	return (EXIT_SUCCESS);
}



// PATH : Liste des répertoires où le shell cherche les exécutables
// HOME : Chemin vers le répertoire home de l'utilisateur
// USER : Nom de l'utilisateur connecté
// PWD : Répertoire de travail actuel
// SHELL : Chemin vers le shell utilisé
// TERM : Type de terminal utilisé