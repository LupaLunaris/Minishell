/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:22:46 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/29 16:16:59 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_exit(t_cmd *cmd, t_shell_data *data)
{
	int exit_code;
	printf("EEEEEXXXXXXIIIIITTTT\n");
	if (data->interactive)
		ft_putendl_fd("exit", 2);
	if (!cmd->args[1])
		exit_code = data->exit_status;
	else
	{
		int i = 0;
		if (cmd->args[1][i] == '-' || cmd->args[1][i] == '+')
			i++;
		while (cmd->args[1][i])
		{
			if (!ft_isdigit(cmd->args[1][i]))
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(cmd->args[1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				exit(2);
			}
			i++;
		}
		if (cmd->args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return 1;
		}
		exit_code = ft_atoi(cmd->args[1]);
	}
	exit(exit_code & 0xFF);
	return exit_code;
}
