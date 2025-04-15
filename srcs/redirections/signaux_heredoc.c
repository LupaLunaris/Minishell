/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:58:43 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/15 11:49:15 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minishell.h"
#include <signal.h>

extern volatile sig_atomic_t	g_signal_received;
/* Signal handler spécifique au heredoc */
void signal_handler_heredoc(int signo)
{
	g_signal_received = signo;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

/* Configuration des signaux pour heredoc */
void	set_signals_heredoc(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &signal_handler_heredoc;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/* Restauration des signaux à leur état par défaut (normal hors heredoc) */
void	restore_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
