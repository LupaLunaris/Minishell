/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:35:56 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/09 13:46:53 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Convert process termination status to shell exit code */
int	handle_status(int save_status)
{
	if (WIFSIGNALED(save_status))
		return (128 + WTERMSIG(save_status));
	else if (WIFEXITED(save_status))
		return (WEXITSTATUS(save_status));
	return (save_status);
}

/* Convert environment linked list to array format for execve */
char	**env_list_to_array(t_env_list *env_list)
{
	int			count;
	t_env_list	*temp;
	char		**env_array;
	int			i;

	temp = env_list;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	temp = env_list;
	while (temp)
	{
		env_array[i] = ft_strjoin_env(temp->key, temp->value);
		temp = temp->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

/* Check if command has any heredoc redirections */
int	has_heredoc(t_cmd *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			return (1);
		redir = redir->next;
	}
	return (0);
}

/* Retrieve heredoc content from command redirections */
char	*get_cmd_heredoc_content(t_cmd *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			return (redir->heredoc_content);
		redir = redir->next;
	}
	return (NULL);
}

/* Get delimiter string for heredoc from command redirections */
char	*get_heredoc_delimiter(t_cmd *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			return (redir->file);
		redir = redir->next;
	}
	return (NULL);
}
