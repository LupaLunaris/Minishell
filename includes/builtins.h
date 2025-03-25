/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:08:00 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/19 17:36:39 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "command.h"
# include "env.h"
# include "shell_data.h"

// Fonctions builtins
int 			execute_builtin(t_cmd *cmd, t_shell_data *data);
int             builtin_echo(t_cmd *cmd);
int				builtin_cd(char **args, t_env_list **env_list);
int             builtin_pwd(void);
int             builtin_exit(t_cmd *cmd, t_shell_data *data);
int             builtin_export(t_cmd *cmd,  t_env_list **env_list);
int             builtin_unset(char **args,  t_env_list **env_list);
int             builtin_env(t_cmd *cmd, t_env_list **env_list);

#endif
