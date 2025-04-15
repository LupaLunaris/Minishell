/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:28:22 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/15 11:49:39 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to display error messages */
int	error_handler(const char *cmd, const char *message,
	int should_exit, int error_code)
{
	if (message && ft_strlen(message) > 0)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		if (cmd)
		{
			write(STDERR_FILENO, cmd, ft_strlen(cmd));
			write(STDERR_FILENO, ": ", 2);
		}
		write(STDERR_FILENO, message, ft_strlen(message));
		write(STDERR_FILENO, "\n", 1);
	}
	if (should_exit)
		exit(error_code);
	return (error_code);
}

int	error_handler_c(t_cmd *cmd, char **env_array, const char *message,
	int should_exit)
{
	if (message && ft_strlen(message) > 0)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		if (cmd->cmd)
		{
			write(STDERR_FILENO, cmd->cmd, ft_strlen(cmd->cmd));
			write(STDERR_FILENO, ": ", 2);
		}
		write(STDERR_FILENO, message, ft_strlen(message));
		write(STDERR_FILENO, "\n", 1);
	}
	if(cmd)
		free_command(cmd);
	if (env_array)
		free_env_array(env_array);
	if (should_exit)
		exit(127);
	return (127);
}


/* Function to clean up resources and exit the shell */
void	cleanup_and_exit(t_shell_data *data, t_cmd *cmds, int exit_code)
{
	if (cmds)
		free_command(cmds);
	if (data)
		free_shell_data(data);
	rl_clear_history();
	exit(exit_code);
}
