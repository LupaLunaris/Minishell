/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:17:31 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/06 11:13:21 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Gère le statut de sortie selon les signaux */
void	handle_signals_exit_status(t_shell_data *data)
{
	if (g_signal_received == SIGINT)
		data->exit_status = 130;
	else if (g_signal_received == SIGQUIT)
		data->exit_status = 131;
}

void	handle_input_loop(t_shell_data *data, char **rl)
{
	*rl = readline("MiniShellDeLaMort> ");
	if (*rl == NULL)
	{
		if (data->interactive)
			write(STDOUT_FILENO, "exit\n", 5);
		return ;
	}
	if ((*rl)[0] != '\0')
		add_history(*rl);
	set_signals_noninteractive();
	data->exit_status = process_command(*rl, data);
	handle_signals_exit_status(data);
	free(*rl);
}

int	main(int argc, char **argv, char **envp)
{
	char			*rl;
	t_shell_data	*data;

	rl = NULL;
	if (argc != 1 || !argv)
		return (error_handler(NULL, "Invalid arguments", 1, 1));
	data = init_shell_data(envp);
	if (!data)
		return (error_message_and_exit("malloc", "Memory allocation failed"));
	if (!data->env_list)
		return (error_message_env_init(data));
	main_shell_loop(data, &rl);
	cleanup_and_exit(data, NULL, data->exit_status);
	return (data->exit_status);
}
