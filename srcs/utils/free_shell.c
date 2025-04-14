/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:14:57 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/12 20:22:35 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_env_list *env_list)
{
	t_env_list	*current;
	t_env_list	*next;

	current = env_list;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

/* Free environment variable array */
void	free_env_array(char **env_array)
{
	int	i;

	i = 0;
	if (!env_array)
		return ;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

/* Free redirection structures in a command */
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

/* Free array of string arguments */
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

/* Free command structures and all their contents */
void free_command(t_cmd *cmd)
{
    t_cmd *tmp;

    tmp = NULL;
    while (cmd)
    {
        tmp = cmd->next;
        if (cmd->infile > 2)
            close(cmd->infile);
        if (cmd->outfile > 2)
            close(cmd->outfile);
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
