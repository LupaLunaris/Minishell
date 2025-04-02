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

int execute_builtin(t_cmd *cmd, t_shell_data *data)
{
    int ret = 0;

    if (!ft_strcmp(cmd->cmd, "echo"))
        ret = builtin_echo(cmd);
    else if (!ft_strcmp(cmd->cmd, "cd"))
        ret = builtin_cd(cmd->args, &data->env_list);
    else if (!ft_strcmp(cmd->cmd, "pwd"))
        ret = builtin_pwd();
    else if (!ft_strcmp(cmd->cmd, "exit"))
        ret = builtin_exit(cmd, data);
    else if (!ft_strcmp(cmd->cmd, "export"))
        ret = builtin_export(cmd, &data->env_list);
    else if (!ft_strcmp(cmd->cmd, "unset"))
        ret = builtin_unset(cmd->args, &data->env_list);
    else if (!ft_strcmp(cmd->cmd, "env"))
        ret = builtin_env(cmd, &data->env_list);
    else
        ret = 127;
    
    // Mettre à jour le code de sortie
    data->exit_status = ret;
    
    return ret;
}
