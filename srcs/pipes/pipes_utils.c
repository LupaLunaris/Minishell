/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:54:49 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/06 11:58:00 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipeline(t_pipe_data *pd, t_shell_exec *se,
		t_env_list *env_list, t_cmd *cmd_list)
{
	t_cmd	*curr;
	int		count;

	se->env_list = env_list;
	count = 0;
	curr = cmd_list;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	pd->cmd_count = count;
	pd->i = 0;
	pd->pipes[0][0] = -1;
	pd->pipes[0][1] = -1;
	pd->pipes[1][0] = -1;
	pd->pipes[1][1] = -1;
}

int	create_process(t_cmd *curr, t_pipe_data *pd, t_shell_exec *se)
{
	pid_t	pid;

	if (pd->i < pd->cmd_count - 1 && pipe(pd->pipes[pd->i % 2]) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		manage_pipes(pd, 1);
		process_pipe_command(curr, se);
	}
	manage_pipes(pd, 0);
	return (pid);
}

int	wait_for_processes(t_cmd *cmd, int *last_status)
{
	t_cmd	*curr;
	int		status;

	curr = cmd;
	while (curr)
	{
		waitpid(curr->pid, &status, 0);
		if (WIFEXITED(status))
			*last_status = WEXITSTATUS(status);
		curr = curr->next;
	}
	return (*last_status);
}
