/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pipes.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: Jpaulis <Jpaulis@student.s19.be>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 18:01:14 by Jpaulis		   #+#	#+#			 */
/*   Updated: 2025/03/19 17:34:36 by Jpaulis		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

/*
 * Sets up pipe redirections for each process in the pipeline
 * Based on whether it's a child process or parent process
 * 
 * For child: redirects stdin/stdout to appropriate pipe ends
 * For parent: closes unused pipe ends to prevent hanging
 */
void	manage_pipes(t_pipe_data *pd, int is_child)
{
	if (is_child)
	{
		if (pd->i > 0)
			dup2(pd->pipes[(pd->i - 1) % 2][0], STDIN_FILENO);
		if (pd->i < pd->cmd_count - 1)
			dup2(pd->pipes[pd->i % 2][1], STDOUT_FILENO);
		if (pd->pipes[0][0] != -1)
			close(pd->pipes[0][0]);
		if (pd->pipes[0][1] != -1)
			close(pd->pipes[0][1]);
		if (pd->pipes[1][0] != -1)
			close(pd->pipes[1][0]);
		if (pd->pipes[1][1] != -1)
			close(pd->pipes[1][1]);
	}
	else
	{
		if (pd->i > 0)
			close(pd->pipes[(pd->i - 1) % 2][0]);
		if (pd->i < pd->cmd_count - 1)
			close(pd->pipes[pd->i % 2][1]);
	}
}

/*
 * Processes a single command in a pipeline
 * Sets up redirections, then either:
 * - Executes a builtin command, or
 * - Executes an external command
 */
void	process_pipe_command(t_cmd *curr, t_shell_exec *se)
{
	char	**env_array;

	if (setup_redirection(curr->redirections) != 0)
		exit(EXIT_FAILURE);
	if (curr->is_builtin)
		exit(execute_builtin(curr, se->data));
	else
	{
		env_array = env_list_to_array(se->env_list);
		execute_command(curr, env_array);
	}
}

/*
 * Executes a pipeline of commands using multiple processes
 * Creates processes for each command, sets up pipes between them,
 * and waits for all processes to complete
 * 
 * Returns: Exit status of the last command in the pipeline
 */
int	execute_pipeline(t_cmd *cmd, t_env_list *env_list, t_shell_data *data)
{
	t_pipe_data		pd;
	t_cmd			*curr;
	t_shell_exec	se;
	int				last_status;

	last_status = 0;
	init_pipeline(&pd, &se, env_list, cmd);
	se.data = data;
	curr = cmd;
	while (curr)
	{
		curr->pid = create_process(curr, &pd, &se);
		if (curr->pid == -1)
			return (EXIT_FAILURE);
		curr = curr->next;
		pd.i++;
	}
	return (wait_for_processes(cmd, &last_status));
}
