/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:51:39 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/30 14:51:39 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Execute command with absolute/relative path and check permissions */
static int	handle_direct_path(t_cmd *cmd, char **env_array)
{
	struct stat	file_stat;

	if (access(cmd->cmd, F_OK) != 0)
		error_handler_c(cmd, env_array ,"No such file or directory", 1);
	if (stat(cmd->cmd, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
			error_handler(cmd->cmd, "Is a directory", 1, 126);
		if (access(cmd->cmd, X_OK) != 0)
			error_handler(cmd->cmd, "Permission denied", 1, 126);
	}
	execve(cmd->cmd, cmd->args, env_array);
	return (error_handler(cmd->cmd, "Error executing command", 1, 126));
}

/* Find command in PATH and execute it */
static int	handle_cmd_path(t_cmd *cmd, char **env_array)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd->cmd, env_array);
	if (cmd_path)
	{
		execve(cmd_path, cmd->args, env_array);
		free(cmd_path);
		return (error_handler(cmd->cmd, "Error executing command", 1, 126));
	}
	return (error_handler_c(cmd, env_array ,"command not found", 1));
}

/* Special version of command execution for heredoc processing */
int	execute_command_for_heredoc(t_cmd *cmd, char **env_array)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd->cmd, env_array);
	if (!cmd_path)
		return (error_handler_c(cmd, env_array ,"command not found", 1));
	execve(cmd_path, cmd->args, env_array);
	perror("execve");
	free(cmd_path);
	return (EXIT_FAILURE);
}

/* Main command execution function that determines execution method */
void	execute_command(t_cmd *cmd, char **env_array)
{
	if (cmd->cmd && ((cmd->cmd[0] == '$' && cmd->cmd[1] == '\0')
			|| (cmd->cmd[0] == '$' && cmd->cmd[1] == '?'
				&& cmd->cmd[2] == '\0')))
		error_handler_c(cmd, env_array ,"command not found", 1);
	if (strchr(cmd->cmd, '/'))
		handle_direct_path(cmd, env_array);
	else
		handle_cmd_path(cmd, env_array);
}
