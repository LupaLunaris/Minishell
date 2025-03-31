/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:28:22 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 18:42:53 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
int	error_handler(const char *cmd, const char *message, int should_exit, int error_code)
{
	if (message && strlen(message) > 0)
	{
		if (cmd)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, cmd, strlen(cmd));
			write(STDERR_FILENO, ": ", 2);
		}
		else
			write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, message, strlen(message));
		write(STDERR_FILENO, "\n", 1);
	}
	if (should_exit)
		exit(error_code);
	return (error_code);
}

void cleanup_and_exit(const char *cmd, const char *message, t_shell_data *data, t_cmd *cmds, int exit_code)
{
    // Libérer les ressources
    if (cmds)
        free_command(cmds);
    if (data)
    {
        if (data->env_list)
            free_env_list(data->env_list);
        free(data);
    }
    rl_clear_history();
    
    // Afficher le message d'erreur si nécessaire et quitter
    if (message || cmd)
        error_handler(cmd, message, 1, exit_code);
    else
        exit(exit_code);
}
