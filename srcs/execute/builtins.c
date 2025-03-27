/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   builtins.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: Jpaulis <Jpaulis@student.s19.be>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 18:02:55 by Jpaulis		   #+#	#+#			 */
/*   Updated: 2025/03/19 17:35:48 by Jpaulis		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

// int	is_builtin(char *cmd)
// {
// 	return (
// 		!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") ||
// 		!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
// 		!ft_strcmp(cmd, "exit")
// 	);
// }

int execute_builtin(t_cmd *cmd, t_shell_data *data)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (builtin_echo(cmd));
	else if (!ft_strcmp(cmd->cmd, "cd"))
		return (builtin_cd(cmd->args, &data->env_list));
	// else if (!ft_strcmp(cmd->cmd, "pwd"))
	//	 return (builtin_pwd());
	else if (!ft_strcmp(cmd->cmd, "exit"))
		return (builtin_exit(cmd, data));
	else if (!ft_strcmp(cmd->cmd, "export"))
		return (builtin_export(cmd, &data->env_list));
	else if (!ft_strcmp(cmd->cmd, "unset"))
		return (builtin_unset(cmd->args, &data->env_list));
	else if (!ft_strcmp(cmd->cmd, "env"))
		return (builtin_env(cmd, &data->env_list));
	return (1);
}
