/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:17:31 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/12 20:07:17 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Updates exit status based on received signals
 * (130 for SIGINT, 131 for SIGQUIT)
 */
void	handle_signals_exit_status(t_shell_data *data)
{
	if (g_signal_received == SIGINT)
		data->exit_status = 130;
	else if (g_signal_received == SIGQUIT)
		data->exit_status = 131;
}

/*
 * Handles a single iteration of shell input: gets command,
 * adds to history, processes it, and manages signals
 */
void	handle_input_loop(t_shell_data *data, char **rl)
{
	int	signal_was_received;

	signal_was_received = (g_signal_received == SIGINT);
	if (g_signal_received != 0)
	{
		handle_signals_exit_status(data);
		g_signal_received = 0;
	}
	if (!signal_was_received)
		*rl = readline("MiniShellDeLaMort> ");
	else
		*rl = readline("");
	if (*rl == NULL)
	{
		if (data->interactive)
			write(STDOUT_FILENO, "exit\n", 5);
		data->should_exit = 1;
		return ;
	}
	if ((*rl)[0] != '\0')
		add_history(*rl);
	set_signals_noninteractive();
	data->exit_status = process_command(*rl, data);
	handle_signals_exit_status(data);
	free(*rl);
}

/*
 * Main shell function: initializes data, runs command loop,
 * and cleans up before exiting
 */
int	main(int argc, char **argv, char **envp)
{
	char			*rl;
	t_shell_data	*data;

	rl = NULL;
	if (argc != 1 || !argv)
		return (error_handler(NULL, "Invalid arguments", 1, 1));
	data = init_shell_data(envp);
	if (!data)
		return (error_handler("malloc", "Memory allocation failed",
				1, EXIT_FAILURE));
	if (!data->env_list)
		return (error_message_env_init(data));
	main_shell_loop(data, &rl);
	return (data->exit_status);
}
