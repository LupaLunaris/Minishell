/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   execute.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: Jpaulis <Jpaulis@student.s19.be>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 18:00:06 by Jpaulis		   #+#	#+#			 */
/*   Updated: 2025/03/19 17:34:15 by Jpaulis		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int	get_children(t_cmd *cmd)
{
	t_cmd	*head;
	pid_t	wpid;
	int		status;
	int		save_status;

	head = cmd;
	status = 0;
	save_status = 0;
	while (1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid <= 0)
			break ;
		cmd = head;
		while (cmd)
		{
			if (wpid == cmd->pid)
			{
				save_status = status;
				break ;
			}
			cmd = cmd->next;
		}
	}
	return (handle_status(save_status));
}

static void	child_process(t_cmd *cmd, char **env_array, t_shell_data *data)
{
	setup_redirection(cmd->redirections);
	if (cmd->is_builtin)
		exit(execute_builtin(cmd, data));
	else
		execute_command(cmd, env_array);
}

int	create_children(t_cmd *cmd, t_env_list *env_list, t_shell_data *data)
{
	t_cmd	*head;
	char	**env_array;
	pid_t	pid;
	int		status;

	env_array = env_list_to_array(env_list);
	head = cmd;
	while (cmd)
	{
		pid = fork();
		if (pid == -1)
		{
			free_env_array(env_array);
			return (error_handler("fork", strerror(errno), 0, EXIT_FAILURE));
		}
		cmd->pid = pid;
		if (pid == 0)
			child_process(cmd, env_array, data);
		cmd = cmd->next;
	}
	status = get_children(head);
	data->exit_status = status;
	free_env_array(env_array);
	return (status);
}

static int	process_cmd_heredocs(t_cmd *cmd)
{
	t_cmd	*curr;
	int		status;
	char	*delimiter;

	curr = cmd;
	while (curr)
	{
		if (has_heredoc(curr))
		{
			delimiter = get_heredoc_delimiter(curr);
			if (delimiter && (!get_cmd_heredoc_content(curr)
					|| ft_strlen(get_cmd_heredoc_content(curr)) == 0))
			{
				status = process_heredoc(delimiter, curr);
				if (status != 0)
					return (status);
			}
		}
		curr = curr->next;
	}
	return (0);
}

int	execute(t_cmd *cmd, t_env_list *env_list, t_shell_data *data)
{
	int	status;

	status = process_cmd_heredocs(cmd);
	if (status != 0)
		return (status);
	if (!cmd)
		return (EXIT_SUCCESS);
	if (cmd->next)
		return (execute_pipeline(cmd, env_list, data));
	if (cmd->is_builtin)
		return (execute_builtin_cmd(cmd, data));
	return (create_children(cmd, env_list, data));
}
