/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   builtins.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: Jpaulis <Jpaulis@student.s19.be>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 18:02:55 by Jpaulis		   #+#	#+#			 */
/*   Updated: 2025/03/19 17:35:48 by Jpaulis		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_cmd *cmd, t_shell_data *data)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(cmd->cmd, "echo"))
		ret = builtin_echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		ret = builtin_cd(cmd->args, &data->env_list);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		ret = builtin_pwd();
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ret = builtin_exit(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "export"))
		ret = builtin_export(cmd, &data->env_list);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		ret = builtin_unset(cmd->args, &data->env_list);
	else if (!ft_strcmp(cmd->cmd, "env"))
		ret = builtin_env(cmd, &data->env_list);
	else
		ret = 127;
	data->exit_status = ret;
	return (ret);
}

static int	has_redirections(t_cmd *cmd)
{
	return (cmd->redirections != NULL);
}

int	execute_builtin_cmd(t_cmd *cmd, t_shell_data *data)
{
	int	stdin_backup;
	int	stdout_backup;
	int	ret;

	stdin_backup = -1;
	stdout_backup = -1;
	if (has_redirections(cmd))
	{
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
	}
	setup_redirection(cmd->redirections);
	ret = execute_builtin(cmd, data);
	restore_io(stdin_backup, stdout_backup);
	return (ret);
}
