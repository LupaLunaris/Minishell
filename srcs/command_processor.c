/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:44:41 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/05 23:20:03 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Vérifie et traite les commandes spéciales */
// int	check_special_commands(char *input, t_cmd *cmd)
// {
// 	char	*comd;

// 	comd = cmd->args[0];
// 	if (!input || input[0] == '\0')
// 		return (1);
// 	if (ft_strcmp(input, "$") == 0 || ft_strcmp(input, "$?") == 0)
// 	{
// 		ft_putstr_fd("minishell1 : ", 2);
// 		ft_putstr_fd(comd, 2);
// 		ft_putstr_fd(" : command not found\n", 2);
// 		return (127);
// 	}
// 	return (0);
// }

// /* Vérifie les commandes qui commencent par $ */
// int	check_dollar_command(t_cmd *cmd_list)
// {
// 	if (cmd_list && cmd_list->cmd && cmd_list->cmd[0] == '$')
// 	{
// 		if (!ft_strchr(cmd_list->cmd, '/'))
// 		{
// 			clean_cmd_list(cmd_list);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// /* Traite une commande saisie par l'utilisateur */
// int	process_command(char *input, t_shell_data *data)
// {
// 	t_cmd	*cmd_list;
// 	int		ret;
// 	int		special_code;

// 	cmd_list = parse_input(input);
// 	var_expend(data->env_list, cmd_list, data);
// 	special_code = check_special_commands(input,cmd_list);
// 	if (special_code)
// 	{
// 		if (special_code == 127)
// 			return (127);
// 		return (special_code - 1);
// 	}
// 	if (!cmd_list)
// 		return (1);
// 	if (process_all_redirections(cmd_list) != 0)
// 		return (1);
// 	if (check_dollar_command(cmd_list))
// 		return (0);
// 	ret = execute(cmd_list, data->env_list, data);
// 	clean_cmd_list(cmd_list);
// 	return (ret);
// }
int	check_special_commands(char *input)
{
	if (!input || input[0] == '\0')
		return (1);
	if (ft_strcmp(input, "$") == 0 )//|| ft_strcmp(input, "$?") == 0)
	{
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	return (0);
}

/* Vérifie les commandes qui commencent par $ */
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

/* Traite une commande saisie par l'utilisateur */
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
	if (process_all_redirections(cmd_list) != 0)
		return (1);
	var_expend(data->env_list, cmd_list, data);
	if (check_dollar_command(cmd_list))
		return (0);
	ret = execute(cmd_list, data->env_list, data);
	clean_cmd_list(cmd_list);
	return (ret);
}