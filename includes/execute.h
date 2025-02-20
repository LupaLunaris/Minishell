/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:56:35 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/20 15:31:24 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
// Exécuter une commande simple
int    execute_command(t_command *cmd, char **envp);

// Gestion des pipes
void    handle_pipes(t_command *cmd, char **envp);

// Gestion des redirections
void    setup_redirection(const char *input_file, const char *output_file, int append);

// Builtins
int     is_builtin(char *cmd);        // Vérifie si c'est un builtin
int    execute_builtin(t_command *cmd, t_env_list *env_list);

// Fonctions utilitaires (si nécessaires)
void    free_command(t_command *cmd); // Fonction pour nettoyer une commande
void    print_command(t_command *cmd);// Debug : imprime une commande


#endif