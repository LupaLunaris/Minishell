/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:03:59 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/03 20:52:00 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Print command details (for debugging)
 */
void	print_cmd(t_cmd *cmd)
{
	int				i;
	t_redirection	*redir;

	if (!cmd)
	{
		printf("Command is NULL.\n");
		return ;
	}
	printf("Command name: %s\n", cmd->cmd);
	if (cmd->args)
	{
		i = 0;
		printf("Arguments:\n");
		while (cmd->args[i])
		{
			printf("  - %s\n", cmd->args[i]);
			i++;
		}
	}
	redir = cmd->redirections;
	print_redirections(redir);
}

/**
 * Print redirection details (for debugging)
 */
void	print_redirections(t_redirection *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_INPUT)
			printf("Input redirection: %s\n", redir->file);
		else if (redir->type == REDIR_OUTPUT)
			printf("Output redirection: %s\n", redir->file);
		else if (redir->type == REDIR_APPEND)
			printf("Append redirection: %s\n", redir->file);
		else if (redir->type == REDIR_HEREDOC)
			printf("Heredoc redirection\n");
		else
			printf("Unknown redirection type: %d\n", redir->type);
		redir = redir->next;
	}
}
