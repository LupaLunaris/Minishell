/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:07:53 by malafont          #+#    #+#             */
/*   Updated: 2025/04/04 10:07:57 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_redirection(t_redirection *new_redir, char *file, int type)
{
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
		return (0);
	new_redir->type = type;
	new_redir->heredoc_content = NULL;
	new_redir->next = NULL;
	return (1);
}
/* Ajoute une redirection à une commande */

static int	add_redirection(t_cmd *cmd, char *file, int type)
{
	t_redirection	*new_redir;
	t_redirection	*curr;

	new_redir = (t_redirection *)malloc(sizeof(t_redirection));
	if (!new_redir)
		return (0);
	if (!new_redirection(new_redir, file, type))
	{
		free(new_redir);
		return (0);
	}
	if (!cmd->redirections)
		cmd->redirections = new_redir;
	else
	{
		curr = cmd->redirections;
		while (curr->next)
			curr = curr->next;
		curr->next = new_redir;
	}
	return (1);
}

static int	is_token_word(t_cmd *cmd, t_token **token)
{
	if (!*token || (*token)->type != TOKEN_WORD)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
		clean_cmd_list(cmd);
		return (0);
	}
	return (1);
}

int	add_token_redir(t_cmd *cmd, t_token **token)
{
	int	redir_type;

	if ((*token)->type == TOKEN_REDIR_IN || (*token)->type == TOKEN_REDIR_OUT
		|| (*token)->type == TOKEN_APPEND || (*token)->type == TOKEN_HEREDOC)
	{
		redir_type = 0;
		if ((*token)->type == TOKEN_REDIR_IN)
			redir_type = REDIR_INPUT;
		else if ((*token)->type == TOKEN_REDIR_OUT)
			redir_type = REDIR_OUTPUT;
		else if ((*token)->type == TOKEN_APPEND)
			redir_type = REDIR_APPEND;
		else if ((*token)->type == TOKEN_HEREDOC)
			redir_type = REDIR_HEREDOC;
		*token = (*token)->next;
		if (!is_token_word(cmd, token))
			return (0);
		if (!add_redirection(cmd, (*token)->value, redir_type))
		{
			clean_cmd_list(cmd);
			return (0);
		}
	}
	return (1);
}
