/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:11:35 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/30 20:36:41 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_cmd *cmd)
{
    int i;
    int newline;

    i = 1; // Pour parcourir les arguments
    newline = 1; // Vérifie si une nouvelle ligne doit être ajoutée

    // Gérer option(s) -n (potentiellement répétées)
    while (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0)
    {
        int j = 2; // Parcourir après "-n"
        while (cmd->args[i][j] == 'n') // Vérifie si tous les caractères après "-" sont des "n"
            j++;
        if (cmd->args[i][j] != '\0') // Si un caractère non "n" est rencontré, ce n'est plus une option valide
            break;
        newline = 0; // Ne pas ajouter de nouvelle ligne
        i++; // Passer à l'argument suivant
    }
    
    // Afficher tous les arguments restants
    while (cmd->args[i])
    {
        write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i])); // Affiche l'argument
        if (cmd->args[i + 1]) // Ajouter un espace après chaque argument (sauf le dernier)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }

    // Ajouter une nouvelle ligne si option "-n" n'est pas activée
    if (newline)
        write(STDOUT_FILENO, "\n", 1);

    // Retourne EXIT_SUCCESS
    return (EXIT_SUCCESS);
}
