/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:48:10 by malafont          #+#    #+#             */
/*   Updated: 2025/04/04 09:48:19 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}

static void	clean_redir(t_redirection *redir_curr)
{
	t_redirection	*redir_tmp;

	while (redir_curr)
	{
		redir_tmp = redir_curr->next;
		if (redir_curr->file)
			free(redir_curr->file);
		if (redir_curr->heredoc_content)
			free(redir_curr->heredoc_content);
		free(redir_curr);
		redir_curr = redir_tmp;
	}
}

void	*clean_cmd_list(t_cmd *head)
{
	t_cmd			*curr;
	t_cmd			*tmp;
	t_redirection	*redir_curr;

	curr = head;
	while (curr)
	{
		tmp = curr->next;
		if (curr->cmd)
			free(curr->cmd);
		if (curr->args)
			free_arr(curr->args);
		if (curr->redirections)
		{
			redir_curr = curr->redirections;
			clean_redir(redir_curr);
		}
		free(curr);
		curr = tmp;
	}
	return (NULL);
}
