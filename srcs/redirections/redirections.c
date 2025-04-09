/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:00:51 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/09 13:33:13 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Sets up output redirection to a file (truncate or append mode)
 * Returns: 0 on success, EXIT_FAILURE on error
 */
int	setup_output_redirection(const char *output_file, int append)
{
	int		fd_out;
	int		flags;
	char	*cleaned_file;

	cleaned_file = strip_quotes((char *)output_file);
	if (!cleaned_file)
		return (error_handler("file", "memory allocation failed",
				1, EXIT_FAILURE));
	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd_out = open(cleaned_file, flags, 0644);
	if (fd_out == -1)
	{
		error_handler(cleaned_file, strerror(errno), 1, EXIT_FAILURE);
		free(cleaned_file);
		return (EXIT_FAILURE);
	}
	return (handle_dup_output(fd_out, cleaned_file));
}

/*
 * Redirects stdout to given file descriptor and cleans up resources
 */
int	handle_dup_output(int fd_out, char *cleaned_file)
{
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		close(fd_out);
		error_handler(cleaned_file, strerror(errno), 1, EXIT_FAILURE);
		free(cleaned_file);
		return (EXIT_FAILURE);
	}
	close(fd_out);
	free(cleaned_file);
	return (0);
}

/*
 * Restores original stdin/stdout file descriptors
 */
void	restore_io(int stdin_fd, int stdout_fd)
{
	if (stdin_fd >= 0)
	{
		dup2(stdin_fd, STDIN_FILENO);
		close(stdin_fd);
	}
	if (stdout_fd >= 0)
	{
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdout_fd);
	}
}

/*
 * Processes a single redirection based on its type
 */
static int	process_redirection(t_redirection *current, char *cleaned_file)
{
	if (current->type == REDIR_INPUT)
		return (handle_input_redir(cleaned_file));
	else if (current->type == REDIR_OUTPUT)
		return (handle_output_redir(cleaned_file, 0));
	else if (current->type == REDIR_APPEND)
		return (handle_output_redir(cleaned_file, 1));
	else if (current->type == REDIR_HEREDOC)
		return (handle_heredoc_redir(current, cleaned_file));
	return (0);
}

/*
 * Sets up all redirections for a command
 * Returns: 0 on success, error code on failure
 */
int	setup_redirection(t_redirection *redirections)
{
	t_redirection	*current;
	char			*cleaned_file;
	int				result;

	current = redirections;
	while (current)
	{
		cleaned_file = strip_quotes(current->file);
		if (!cleaned_file)
			return (error_handler("file", "memory allocation failed",
					1, EXIT_FAILURE));
		result = process_redirection(current, cleaned_file);
		free(cleaned_file);
		if (result != 0)
			return (result);
		current = current->next;
	}
	return (0);
}
