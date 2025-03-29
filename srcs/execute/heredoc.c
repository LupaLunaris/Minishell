/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:44:57 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/29 17:10:10 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Initialise le pipe pour le heredoc
 * Renvoie 0 en cas de succès, -1 en cas d'échec
 */
static int init_heredoc_pipe(int pipe_fd[2])
{
    if (pipe(pipe_fd) == -1)
        return (error_handler("heredoc", "pipe creation failed", 0, 1));
    return (0);
}

/**
 * Lit les entrées jusqu'au délimiteur et les écrit dans le pipe
 * Renvoie 0 en cas de succès, un code d'erreur sinon
 */
static int read_heredoc_input(int pipe_fd[2], char *delimiter)
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            return (error_handler("heredoc", 
                "unexpected EOF while looking for heredoc delimiter", 0, 130));
        }

        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }

        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);
    return (0);
}

/**
 * Prépare les redirections pour exécuter la commande avec le heredoc
 * Renvoie le fd original de stdin à restaurer, ou -1 en cas d'échec
 */
static int setup_heredoc_redirection(int pipe_fd[0])
{
    int original_stdin;

    original_stdin = dup(STDIN_FILENO);
    if (original_stdin == -1)
    {
        close(pipe_fd[0]);
        error_handler("heredoc", "failed to duplicate stdin", 0, 1);
        return (-1);
    }

    if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
    {
        close(pipe_fd[0]);
        close(original_stdin);
        error_handler("heredoc", "failed to redirect stdin", 0, 1);
        return (-1);
    }

    close(pipe_fd[0]);
    return (original_stdin);
}

/**
 * Restaure l'entrée standard après l'exécution de la commande
 * Renvoie 0 en cas de succès, -1 en cas d'échec
 */
static int restore_stdin(int original_stdin)
{
    if (original_stdin != -1)
    {
        if (dup2(original_stdin, STDIN_FILENO) == -1)
        {
            close(original_stdin);
            return (error_handler("heredoc", "failed to restore stdin", 0, 1));
        }
        close(original_stdin);
    }
    return (0);
}

/**
 * Gère tout le processus de heredoc
 * Renvoie le code de statut de la commande ou un code d'erreur
 */
int process_heredoc(char *delimiter, t_cmd *command)
{
    int pipe_fd[2];
    int original_stdin;
    int status;

    if (init_heredoc_pipe(pipe_fd) != 0)
        return (1);
    
    if (read_heredoc_input(pipe_fd, delimiter) != 0)
        return (130);
    
    original_stdin = setup_heredoc_redirection(pipe_fd);
    if (original_stdin == -1)
        return (1);
    
    execute_command(command, NULL); // Replace NULL with the appropriate argument(s) if needed
	status = 0;
    
    restore_stdin(original_stdin);
    
    return (status);
}
