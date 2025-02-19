/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:11:35 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/19 16:54:46 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	builtin_echo(char **args)
{
	int i;
	int newline;

	i = 1;
	newline = 1;
	if (args[i] && strcmp(args[i], "-n") == 0) // Vérifie si le premier argument est l'option "-n"
	{
		newline = 0; // Ne pas ajouter de nouvelle ligne
		i++;         // Passer à l'argument suivant
	}
	while (args[i]) // Afficher tous les arguments restants
	{
		printf("%s", args[i]); // Affiche l'argument
		if (args[i + 1]) // Si un autre argument existe, ajouter un espace
			printf(" ");
		i++;
	}
	if (newline) // Ajouter une nouvelle ligne si l'option "-n" n'est pas spécifiée
		printf("\n");
	return (0); // Succès (retourne un code d'erreur standard)
}
