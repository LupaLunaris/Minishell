/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:14:57 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/08 14:47:08 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_env_list *env_list)
{
	t_env_list	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_shell_data(t_shell_data *data)
{
	if (!data)
		return ;
	if (data->env_list)
		free_env_list(data->env_list);
	if (data->state)
		free(data->state);
	free(data);
}

void	free_redirections(t_redirection *redirections)
{
	t_redirection	*tmp;

	while (redirections)
	{
		tmp = redirections->next;
		if (redirections->file)
			free(redirections->file);
		if (redirections->heredoc_content)
			free(redirections->heredoc_content);
		free(redirections);
		redirections = tmp;
	}
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_command(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->args)
			free_args(cmd->args);
		if (cmd->redirections)
			free_redirections(cmd->redirections);
		free(cmd);
		cmd = tmp;
	}
}
