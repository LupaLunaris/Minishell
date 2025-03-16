/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:08:00 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/15 14:08:05 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "command.h"
# include "env.h"
# include "shell_data.h"

// Fonctions builtins
int             execute_builtin(t_command *cmd, t_shell_data *data);
int             builtin_echo(t_command *cmd);
int             builtin_cd(t_command *cmd, t_shell_data *data);
int             builtin_pwd(void);
int             builtin_exit(t_command *cmd, t_shell_data *data);
int             builtin_export(t_command *cmd, t_shell_data *data);
int             builtin_unset(t_command *cmd, t_shell_data *data);
int             builtin_env(t_command *cmd, t_shell_data *data);

#endif
