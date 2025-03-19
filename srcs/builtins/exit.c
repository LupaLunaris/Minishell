/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:22:46 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/19 14:55:51 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_exit(t_command *cmd, t_shell_data *data)
{
	int exit_code;
	
	// Afficher "exit" en mode interactif
	if (data->interactive)
		ft_putendl_fd("exit", 2);
	// Sans argument, utiliser le statut précédent
	if (!cmd->args[1])
		exit_code = data->exit_status;
	else
	{
		// Vérifier si l'argument est un nombre valide
		int i = 0;
		if (cmd->args[1][i] == '-' || cmd->args[1][i] == '+')
			i++;
		while (cmd->args[1][i])
		{
			if (!ft_isdigit(cmd->args[1][i]))
			{
				// Erreur : argument non numérique
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(cmd->args[1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				exit(2); // Quitter avec statut 2
			}
			i++;
		}
		// Tester s'il y a plus d'un argument
		if (cmd->args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return 1; // Ne pas quitter
		}
		// Convertir l'argument en nombre
		exit_code = ft_atoi(cmd->args[1]);
	}
	// Quitter le shell avec le code de sortie modulo 256
	exit(exit_code & 0xFF);
	return exit_code; // Cette ligne ne sera jamais exécutée
}
