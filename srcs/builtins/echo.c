/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:11:35 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/20 14:42:22 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	builtin_echo(t_command *cmd)
{
	int i;
	int newline;

	i = 1;
	newline = 1;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0) // Vérifie si le premier argument est l'option "-n"
	{
		newline = 0; // Ne pas ajouter de nouvelle ligne
		i++;         // Passer à l'argument suivant
	}
	while (cmd->args[i]) // Afficher tous les arguments restants
	{
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i])); // Affiche l'argument
		if (cmd->args[i + 1]) // Si un autre argument existe, ajouter un espace
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline) // Ajouter une nouvelle ligne si l'option "-n" n'est pas spécifiée
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS); // Succès (retourne un code d'erreur standard)
}
