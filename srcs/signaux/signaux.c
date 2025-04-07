/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:44:56 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/05 19:10:54 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

/* signal_handler:
 * Gestionnaire principal des signaux.
 * Il enregistre le signal reçu et fait le traitement approprié.
 */
void	signal_handler(int signo)
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

/* set_signals_interactive:
 * Configure les gestionnaires de signaux pour le mode interactif.
 * SIGINT (CTRL+C) : afficher un nouveau prompt
 * SIGQUIT (CTRL+\) : ignorer
 */
void	set_signals_interactive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_handler;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

/* set_signals_noninteractive:
 * Configure les gestionnaires pour le mode non-interactif.
 * SIGINT et SIGQUIT sont gérés normalement pour les processus enfants.
 */
void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
