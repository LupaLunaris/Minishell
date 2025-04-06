/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:11:44 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/06 10:20:31 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_cmd_path(char *cmd, char **paths)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_path(char **env_array)
{
	int		i;
	char	*path;

	path = NULL;
	i = 0;
	while (env_array[i])
	{
		if (strncmp(env_array[i], "PATH=", 5) == 0)
		{
			path = env_array[i] + 5;
			break ;
		}
		i++;
	}
	if (!path)
		return (NULL);
	return (path);
}

static int	handle_absolute_path(char *cmd, char **cmd_path)
{
	struct stat	file_stat;

	if (access(cmd, F_OK) == 0)
	{
		if (stat(cmd, &file_stat) == 0 && !S_ISDIR(file_stat.st_mode))
		{
			*cmd_path = ft_strdup(cmd);
			return (1);
		}
	}
	return (0);
}

static char	*process_path_search(char *cmd, char **paths)
{
	char		*cmd_path;
	struct stat	file_stat;

	cmd_path = create_cmd_path(cmd, paths);
	if (cmd_path && stat(cmd_path, &file_stat) == 0
		&& S_ISDIR(file_stat.st_mode))
	{
		free(cmd_path);
		cmd_path = NULL;
	}
	free_arr(paths);
	return (cmd_path);
}

char	*get_cmd_path(char *cmd, char **env_array)
{
	char	*path;
	char	**paths;
	char	*cmd_path;

	if (strchr(cmd, '/'))
	{
		if (handle_absolute_path(cmd, &cmd_path))
			return (cmd_path);
		return (NULL);
	}
	path = get_path(env_array);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (process_path_search(cmd, paths));
}
