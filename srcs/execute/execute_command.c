#include "minishell.h"

static void	free_arr(char **arr)
{
	int  i;

	i = 0;
	if (!arr)
		return;
	while(arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}

char	*create_cdm_path(char *cmd, char **paths)
{
	char	*cmd_path;
	int		i;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		char *tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
		{
			free_arr(paths);
			return cmd_path;
		}
		free(cmd_path);
		cmd_path = NULL;
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
			break;
		}
		i++;
	}
	if (!path)
		return (NULL);
	return (path);
}


char	*get_cmd_path(char *cmd, char **env_array)
{
	char	*path;
	char	**paths;

	path = get_path(env_array);
	if (!path)
		return (NULL);
	if (strchr(cmd, '/'))
		return ft_strdup(cmd);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	char *cmd_path = create_cdm_path(cmd, paths);
	if (cmd_path)
		return cmd_path;
	free_arr(paths);
	printf("no access\n");
	return (NULL);
}


void	execute_command(t_cmd *cmd, char **env_array)
{

	char	*cmd_path;

	cmd_path = get_cmd_path(cmd->cmd, env_array);
	if (cmd_path)
	{
		execve(cmd_path, cmd->args, env_array);
		perror("execve");
		free(cmd_path);
	}
	else
	{
		fprintf(stderr, "command not found: %s\n", cmd->cmd);
	}
	exit(EXIT_FAILURE);
}