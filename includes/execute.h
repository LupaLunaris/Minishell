/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:56:35 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/13 16:32:35 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

// Exécuter une commande simple
int    execute_command(t_command *cmd, char **envp);

// Gestion des pipes
int    handle_pipes(t_command *cmd, char **envp);

// Gestion des redirections
int    setup_redirection(const char *input_file, const char *output_file, int append);

// Builtins
int     is_builtin(char *cmd);        // Vérifie si c'est un builtin
int    execute_builtin(t_command *cmd, t_env_list *env_list);

// Fonctions utilitaires (si nécessaires)
void    free_command(t_command *cmd); // Fonction pour nettoyer une commande
void    print_command(t_command *cmd);// Debug : imprime une commande


#endif