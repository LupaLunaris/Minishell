/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:28:22 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/12 19:11:16 by Jpaulis          ###   ########.fr       */
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
