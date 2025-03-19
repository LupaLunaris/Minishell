/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:56:35 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/19 15:11:24 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "command.h"
# include "env.h"
# include "shell_data.h"

// Fonctions d'exécution
int             execute(t_command *cmd, t_env_list *env_list, t_shell_data *data);
int             execute_pipeline(t_command *cmd, t_shell_data *data);
char            *find_command_path(char *cmd, t_env_list *env_list);
int             wait_for_commands(t_command *cmd_list, t_shell_data *data);
void            execute_single_command(t_command *cmd, t_shell_data *data);
void            execute_external_command(t_command *cmd, t_shell_data *data);
int             is_builtin(char *cmd);

#endif
