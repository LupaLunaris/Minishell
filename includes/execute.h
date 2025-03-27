/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:56:35 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/19 17:36:13 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "command.h"
# include "env.h"
# include "shell_data.h"



// Fonctions d'exécution
int             execute(t_cmd *cmd, t_env_list *env_list, t_shell_data *data);
int				execute_pipeline(t_cmd *cmd, t_env_list *env_list, t_shell_data *data);
char            *find_command_path(char *cmd, t_env_list *env_list);
int             wait_for_commands(t_cmd *cmd_list, t_shell_data *data);
void            execute_single_command(t_cmd *cmd, t_shell_data *data);
void            execute_external_command(t_cmd *cmd, t_shell_data *data);
int 			check_redirections(t_cmd *cmd);
int 			get_children(t_cmd *cmd);
int 			create_children(t_cmd *cmd, t_env_list *env_list, t_shell_data *data);
char			*get_cmd_path(char *cmd, char **env_array);
void			execute_command(t_cmd *cmds, char **env_array);
//static int 		get_children(t_cmd *cmd);

#endif
