/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:02:55 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/19 15:09:38 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_builtin(char *cmd)
{
	return (!strcmp(cmd, "echo") || !strcmp(cmd, "cd") || !strcmp(cmd, "pwd") || 
			!strcmp(cmd, "export") || !strcmp(cmd, "unset") || !strcmp(cmd, "env") || 
			!strcmp(cmd, "exit"));
}

void execute_builtin(t_command *cmd, t_env_list *env_list)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		builtin_echo(cmd->args);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		builtin_cd(cmd->args, env_list);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		builtin_env(env_list);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		builtin_exit(cmd->args);
}	
