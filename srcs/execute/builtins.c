/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:02:55 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/20 14:35:57 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_builtin(char *cmd)
{
	return (
		!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") ||
		!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "exit")
	);
}

int execute_builtin(t_command *cmd, t_env_list *env_list)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (builtin_echo(cmd->args)); // Imprime les arguments
	else if (!ft_strcmp(cmd->cmd, "cd"))
		return (builtin_cd(cmd->args, env_list)); // Change de répertoire
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		return (builtin_pwd()); // Imprime PWD
	else if (!ft_strcmp(cmd->cmd, "exit"))
		builtin_exit(cmd->args); // Quitte Minishell
	else if (!ft_strcmp(cmd->cmd, "export"))
		return (builtin_export(cmd->args, env_list)); // Ajoute/modifie une variable
	else if (!ft_strcmp(cmd->cmd, "unset"))
		return (builtin_unset(cmd->args, env_list)); // Supprime une variable
	if (!ft_strcmp(cmd->cmd, "env"))
		return (builtin_env(cmd->args, env_list)); // Passe les arguments et l'environnement	
	return (1); // En cas d'échec
}
