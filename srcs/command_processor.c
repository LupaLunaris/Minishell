/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:44:41 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/09 14:13:01 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Checks for empty input or the lone "$" special case
 * Returns: 1 for empty, 127 for "$", 0 otherwise
 */
int	check_special_commands(char *input)
{
	if (!input || input[0] == '\0')
		return (1);
	if (ft_strcmp(input, "$") == 0)
	{
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	return (0);
}

/*
 * Handles commands starting with '$' without a path separator
 * Returns: 1 if command starts with $ (no slashes), 0 otherwise
 */
int	check_dollar_command(t_cmd *cmd_list)
{
	if (cmd_list && cmd_list->cmd && cmd_list->cmd[0] == '$')
	{
		if (!ft_strchr(cmd_list->cmd, '/'))
		{
			clean_cmd_list(cmd_list);
			return (1);
		}
	}
	return (0);
}

/*
 * Main command processor: parses input, handles redirections,
 * expands variables, and executes the command
 * Returns: command exit status
 */
int	process_command(char *input, t_shell_data *data)
{
	t_cmd	*cmd_list;
	int		ret;
	int		special_code;

	special_code = check_special_commands(input);
	if (special_code)
	{
		if (special_code == 127)
			return (127);
		return (special_code - 1);
	}
	cmd_list = parse_input(input);
	if (!cmd_list)
		return (1);
	if (process_all_redirections(cmd_list, data) != 0)
		return (1);
	var_expend(data->env_list, cmd_list, data);
	if (check_dollar_command(cmd_list))
		return (0);
	ret = execute(cmd_list, data->env_list, data);
	clean_cmd_list(cmd_list);
	return (ret);
}
