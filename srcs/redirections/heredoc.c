/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:44:57 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/08 16:01:30 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc_line(char *delimiter, char *line,
	char **content, t_shell_data *data)
{
	char	*tmp;
	char	*expanded_line;

	if (!line)
		return (2);
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	expanded_line = expand_variables(line, data);
	free(line);
	tmp = *content;
	*content = ft_strjoin(*content, expanded_line);
	free(tmp);
	tmp = *content;
	*content = ft_strjoin(*content, "\n");
	free(tmp);
	free(expanded_line);
	return (0);
}

static int	read_heredoc_lines(char *delimiter, char **content,
	t_shell_data	*data)
{
	char	*line;
	int		result;
	char	*new_content;

	new_content = ft_strdup("");
	if (!new_content)
		return (error_handler("heredoc", "memory allocation failed", 0, 1));
	while (1)
	{
		line = readline("> ");
		result = handle_heredoc_line(delimiter, line, &new_content, data);
		if (result != 0)
		{
			if (result == 1)
				break ;
			return (result);
		}
	}
	*content = new_content;
	return (0);
}

int	read_heredoc_content(char *delimiter, char **content, t_shell_data *data)
{
	return (read_heredoc_lines(delimiter, content, data));
}

t_redirection	*find_heredoc_redirection(t_cmd *command, char *delimiter)
{
	t_redirection	*redir;

	redir = command->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC
			&& ft_strcmp(redir->file, delimiter) == 0)
			return (redir);
		redir = redir->next;
	}
	return (NULL);
}

int	process_heredoc(char *delimiter, t_cmd *command, t_shell_data	*data)
{
	t_redirection	*redir;
	char			*content;
	int				status;

	redir = find_heredoc_redirection(command, delimiter);
	if (!redir)
		return (0);
	status = read_heredoc_content(delimiter, &content, data);
	if (status != 0)
		return (status);
	if (redir->heredoc_content)
		free(redir->heredoc_content);
	redir->heredoc_content = content;
	return (0);
}
