/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:40:21 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/12 20:07:44 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Main shell loop function */
void	main_shell_loop(t_shell_data *data, char **rl)
{
	while (1)
	{
		g_signal_received = 0;
		if (data->interactive)
			set_signals_interactive();
		handle_input_loop(data, rl);
		if (*rl == NULL || data->should_exit)
			break ;
	}
}

/* Process all redirections for a command list */
int	process_all_redirections(t_cmd *cmd_list, t_shell_data *data)
{
	t_cmd			*curr;
	t_redirection	*redir;
	int				status;

	curr = cmd_list;
	while (curr)
	{
		redir = curr->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				status = process_heredoc(redir->file, curr, data);
				if (status != 0)
				{
					clean_cmd_list(cmd_list);
					return (status);
				}
			}
			redir = redir->next;
		}
		curr = curr->next;
	}
	return (0);
}

/* Handle environment initialization errors */
int	error_message_env_init(t_shell_data *data)
{
	free(data);
	return (error_handler("init_env", "Failed to init env vars", 1,
			EXIT_FAILURE));
}

/* Free all shell data structures */
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

/* Initialize shell data structure */
t_shell_data	*init_shell_data(char **envp)
{
	t_shell_data	*data;

	data = malloc(sizeof(t_shell_data));
	if (!data)
		return (NULL);
	data->exit_status = 0;
	data->interactive = isatty(STDIN_FILENO);
	data->env_list = init_env(envp);
	data->state = NULL;
	data->should_exit = 0;
	return (data);
}
