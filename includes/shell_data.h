/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:37:05 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/05 22:59:50 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_DATA_H
# define SHELL_DATA_H

typedef struct s_shell_data
{
	t_env_list *env_list;    // Stocke l'environnement
    int exit_status;         // Statut de sortie de la dernière commande
    int interactive;         // Mode interactif ou non
	int should_exit;
} t_shell_data;

typedef struct s_shell_exec
{
    t_env_list   *env_list;
    t_shell_data *data;
} t_shell_exec;

typedef struct s_pipe_data
{
    int    i;
    int    cmd_count;
    int	pipes[2][2];
} t_pipe_data;

// Fonctions de gestion des données du shell
t_shell_data    *init_shell_data(char **envp);
void            free_shell_data(t_shell_data *data);
void            update_exit_status(t_shell_data *data, int status);

#endif
