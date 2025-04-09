/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:21:37 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/09 13:49:59 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Resolve target directory path for cd command based on arguments or env */
static int	handle_cd_path(char **args, t_env_list *env_list, char **path)
{
	if (args[1] == NULL)
	{
		*path = get_env_value(env_list, "HOME");
		if (*path == NULL)
			return (error_handler("cd", "HOME not set", 0, 1));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		*path = get_env_value(env_list, "OLDPWD");
		if (*path == NULL)
			return (error_handler("cd", "OLDPWD not set", 0, 1));
		ft_putendl_fd(*path, 1);
	}
	else
		*path = args[1];
	return (0);
}

/* Change directory and update PWD/OLDPWD environment variables */
int	builtin_cd(char **args, t_env_list **env_list)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*path;

	if (args[1] != NULL && args[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (getcwd(old_pwd, PATH_MAX) == NULL)
		return (error_handler("cd", strerror(errno), 0, 1));
	if (handle_cd_path(args, *env_list, &path) != 0)
		return (1);
	if (chdir(path) == -1)
		return (error_handler("cd", strerror(errno), 0, 1));
	if (getcwd(new_pwd, PATH_MAX) == NULL)
		return (error_handler("cd", strerror(errno), 0, 1));
	update_env_var(env_list, "OLDPWD", old_pwd);
	update_env_var(env_list, "PWD", new_pwd);
	return (0);
}
