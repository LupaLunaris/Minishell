/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:37:05 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/15 14:10:44 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_DATA_H
# define SHELL_DATA_H

# include "env.h"

typedef struct s_shell_data
{
    int exit_status;         // Statut de sortie de la dernière commande
    char **history;          // Tableau pour l'historique des commandes
    int interactive;         // Mode interactif ou non
} t_shell_data;

// POUR INITIALISER SHELL DATA :
// t_shell_data *init_shell_data(void)
// {
//     t_shell_data *data = malloc(sizeof(t_shell_data));
//     if (!data)
//         return NULL;
		
//     data->exit_status = 0;
//     data->history = NULL;
//     data->interactive = isatty(STDIN_FILENO); // Détection automatique du mode interactif
	
//     return data;
// }

// Fonctions de gestion des données du shell
t_shell_data    *init_shell_data(char **envp);
void            free_shell_data(t_shell_data *data);
void            update_exit_status(t_shell_data *data, int status);

#endif
