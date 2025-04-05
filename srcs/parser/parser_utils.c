/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:45:05 by malafont          #+#    #+#             */
/*   Updated: 2025/04/03 12:45:12 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_cmdlast(*lst);
	last->next = new;
	new->prev = last;
}

/*
** Crée une nouvelle commande vide
*/
t_cmd	*create_command(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->pid = 0;
	cmd->is_builtin = 0;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	return (cmd);
}

int	count_args(t_token *token, t_token *end)
{
	int	count;

	count = 0;
	while (token != end && token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
			count++;
		else if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
		{
			token = token->next;
			if (!token)
				break ;
		}
		token = token->next;
	}
	return (count);
}

int	init_args(t_cmd *cmd, int arg_count)
{
	int	i;

	if (arg_count == 0)
	{
		cmd->args = (char **)malloc(sizeof(char *));
		if (!cmd->args)
		{
			free(cmd);
			return (0);
		}
		cmd->args[0] = NULL;
	}
	else
	{
		cmd->args = (char **)malloc(sizeof(char *) * (arg_count + 1));
		if (!cmd->args)
		{
			free(cmd);
			return (0);
		}
	}
	i = 0;
	while (i <= arg_count)
		cmd->args[i++] = NULL;
	return (1);
}
