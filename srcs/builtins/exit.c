/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:22:46 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/30 20:27:09 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Vérifie si une chaîne est un nombre valide
 */
static int is_valid_number(char *str)
{
    int i;

    i = 0;

    // Ignorer les espaces au début
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;

    // Gérer le signe
    if (str[i] == '+' || str[i] == '-')
        i++;

    // Vérifier que le reste est composé uniquement de chiffres
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }

    return (1);
}

/**
 * Implémente la commande builtin 'exit'
 * Quitte le shell avec le statut spécifié
 */
int builtin_exit(t_cmd *cmd, t_shell_data *data)
{
    int exit_code;
    char *arg;

    // Code de sortie par défaut (statut de la dernière commande)
    exit_code = data->exit_status;

    // Afficher 'exit' si on est en mode interactif
    if (data->interactive)
        ft_putendl_fd("exit", 2);

    // Si aucun argument, utiliser le statut par défaut
    if (!cmd->args[1])
        exit(exit_code);

    // Sinon, traiter l'argument comme un nombre
    arg = cmd->args[1];

    // Vérifier si c'est un nombre valide
    if (!is_valid_number(arg))
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(arg, 2);
        ft_putendl_fd(": numeric argument required", 2);
        exit(2);
    }

    // Si plus d'un argument, erreur
    if (cmd->args[2])
    {
        ft_putendl_fd("minishell: exit: too many arguments", 2);
        return (1);
    }

    // Convertir l'argument en nombre et quitter
    exit_code = ft_atoi(arg) % 256;
    exit((unsigned char) exit_code);

    // Cette ligne ne sera jamais atteinte
    return exit_code;
}