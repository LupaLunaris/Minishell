/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:09:04 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/15 14:09:07 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "shell_data.h"

// Fonctions de gestion des signaux
void            setup_signals(t_shell_data *data);
void            setup_signals_interactive(void);
void            setup_signals_non_interactive(void);
void            setup_signals_heredoc(void);
void            handle_sigint(int sig);
void            handle_sigquit(int sig);
void            handle_sigint_heredoc(int sig);

#endif
