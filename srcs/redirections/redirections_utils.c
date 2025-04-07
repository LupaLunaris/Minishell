/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:06:37 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/06 12:12:53 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_redir(char *cleaned_file)
{
	int	fd;

	fd = open(cleaned_file, O_RDONLY);
	if (fd < 0)
	{
		error_handler(cleaned_file, strerror(errno), 1, 1);
		free(cleaned_file);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_output_redir(char *cleaned_file, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cleaned_file, flags, 0644);
	if (fd < 0)
	{
		error_handler(cleaned_file, strerror(errno), 1, 1);
		free(cleaned_file);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_heredoc_redir(t_redirection *current, char *cleaned_file)
{
	int	pipe_fd[2];

	if (current->heredoc_content)
	{
		if (pipe(pipe_fd) == -1)
		{
			error_handler("pipe", strerror(errno), 1, 1);
			free(cleaned_file);
			return (1);
		}
		write(pipe_fd[1], current->heredoc_content,
			strlen(current->heredoc_content));
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	return (0);
}

static void	process_char(char *str, char *result, int *i, int *j)
{
	static int	in_squote = 0;
	static int	in_dquote = 0;

	if (str[*i] == '\'' && !in_dquote)
		in_squote = !in_squote;
	else if (str[*i] == '"' && !in_squote)
		in_dquote = !in_dquote;
	else
		result[(*j)++] = str[*i];
	(*i)++;
}

char	*strip_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
		process_char(str, result, &i, &j);
	result[j] = '\0';
	return (result);
}
