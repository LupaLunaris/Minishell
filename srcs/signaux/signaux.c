/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:44:56 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/10 10:51:24 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minishell.h"

/* Global variable to store received signal number */
volatile sig_atomic_t	g_signal_received = 0;

/**
 * Standard signal handler for non-interactive mode
 * SIGINT: print newline, SIGQUIT: no visual output
 */
void	signal_handler(int signo)
{
	g_signal_received = signo;
	if (signo == SIGINT)
		write(1, "\n", 1);
}

/**
 * Signal handler for interactive mode (prompt)
 * SIGINT: print newline and redisplay prompt
 */
void	signal_handler_interactive(int signo)
{
	g_signal_received = signo;
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
 * Sets signal handlers for interactive mode (prompt)
 * SIGINT: displays new prompt, SIGQUIT: ignored
 */
void	set_signals_interactive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_handler_interactive;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

/**
 * Sets up signal handlers for non-interactive mode (executing commands)
 * - SIGINT (Ctrl+C): set global flag and print newline
 * - SIGQUIT (Ctrl+\): set global flag without output
 */
void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
