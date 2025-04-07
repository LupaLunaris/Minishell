/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:22:25 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/02 15:13:39 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Implémente la commande builtin 'env' qui affiche l'environnement
 * @param command La structure de commande contenant les arguments
 * @param env_list Pointeur vers le début de la liste chaînée d'environnement
 * @return Exit status de la commande (0 pour succès, autre pour erreur)
 */
int	builtin_env(t_cmd *cmd, t_env_list **env_list)
{
	if (cmd->args[1] != NULL)
		return (error_handler("env", "too many arguments", 0, EXIT_FAILURE));
	if (!env_list)
		return (error_handler("env",
				"environment not available", 0, EXIT_FAILURE));
	print_env_list(*env_list);
	return (EXIT_SUCCESS);
}
