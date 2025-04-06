/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:09:04 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/06 21:03:48 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

extern volatile sig_atomic_t	g_signal_received;
void							signal_handler(int signo);
void							set_signals_interactive(void);
void							set_signals_noninteractive(void);

#endif
