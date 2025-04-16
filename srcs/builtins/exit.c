/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:22:46 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/15 16:11:43 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if a string represents a valid number for exit command */
static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Implement the 'exit' builtin command to terminate the shell */
int	builtin_exit(t_cmd *cmd, t_shell_data *data)
{
	int		exit_code;
	char	*arg;

	exit_code = data->exit_status;
	if (data->interactive)
		ft_putendl_fd("exit", 2);
	if (!cmd->args[1])
		cleanup_and_exit(data, cmd, exit_code);
	arg = cmd->args[1];
	if (!is_valid_number(arg))
		return (error_handler("exit",
				ft_strjoin(arg, ": numeric argument required"), 1, 2));
	if (cmd->args[2])
		return (error_handler("exit", "too many arguments", 0, 1));
	exit_code = ft_atoi(arg) % 256;
	cleanup_and_exit(data, cmd, exit_code);
	return (exit_code);
}
