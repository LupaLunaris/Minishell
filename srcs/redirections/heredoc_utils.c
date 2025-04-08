/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:03:53 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/08 15:59:13 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_line_to_content(char **new_content, char *line)
{
	char	*temp;

	temp = *new_content;
	*new_content = ft_strjoin(*new_content, line);
	free(temp);
	free(line);
	if (!*new_content)
		return (error_handler("heredoc", "memory allocation failed", 0, 1));
	temp = *new_content;
	*new_content = ft_strjoin(*new_content, "\n");
	free(temp);
	if (!*new_content)
		return (error_handler("heredoc", "memory allocation failed", 0, 1));
	return (0);
}

static int	process_cmd_heredocs(t_cmd *current, t_shell_data *data)
{
	t_redirection	*redir;
	int				status;

	redir = current->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC
			&& (!redir->heredoc_content
				|| ft_strlen(redir->heredoc_content) == 0))
		{
			status = process_heredoc(redir->file, current, data);
			if (status != 0)
				return (status);
		}
		redir = redir->next;
	}
	return (0);
}

int	setup_heredocs_for_pipeline(t_cmd *cmd_list, t_shell_data *data)
{
	t_cmd	*current;
	int		status;

	current = cmd_list;
	while (current)
	{
		status = process_cmd_heredocs(current, data);
		if (status != 0)
			return (status);
		current = current->next;
	}
	return (0);
}

static char	*append_to_content(char *content, char *line)
{
	char	*temp;

	temp = ft_strjoin(content, line);
	free(content);
	free(line);
	content = temp;
	temp = ft_strjoin(content, "\n");
	free(content);
	return (temp);
}

char	*get_heredoc_content(char *delimiter)
{
	char	*content;
	char	*line;

	line = NULL;
	content = ft_strdup("");
	if (!content)
		return (NULL);
	ft_putstr_fd("> ", STDOUT_FILENO);
	while (1)
	{
		line = readline("");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		content = append_to_content(content, line);
		if (!content)
			return (NULL);
		ft_putstr_fd("> ", STDOUT_FILENO);
	}
	return (content);
}
