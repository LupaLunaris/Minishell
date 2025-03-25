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

char *get_cmd_path(char *cmd, char **env_array)
{
	// Si la commande contient déjà un '/', considérer comme chemin absolu
	if (strchr(cmd, '/'))
		return ft_strdup(cmd);

	// Chercher la variable PATH dans l'environnement
	char *path = NULL;
	for (int i = 0; env_array[i]; i++)
	{
		//printf("env_array = %s\n",env_array[i]);
		if (strncmp(env_array[i], "PATH=", 5) == 0)
		{
			path = env_array[i] + 5;
			break;
		}
	}

	if (!path)
		return NULL;

	// Séparer les chemins de PATH et essayer chacun
	char **paths = ft_split(path, ':');
	if (!paths)
		return NULL;

	char *cmd_path = NULL;
	for (int i = 0; paths[i]; i++)
	{
		char *tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		//printf("cdm_path = %s\n",cmd_path);
		// Vérifier si le fichier existe et est exécutable
		if (access(cmd_path, X_OK) == 0)
		{
			free_arr(paths);
			printf("le chemin de la commande existe\n");
			return cmd_path;
		}
		free(cmd_path);
		cmd_path = NULL;
	}

	free_arr(paths);
	printf("no access\n");
	return NULL;
}


void execute_command(t_cmd *cmds, char **env_array)
{
	t_cmd *current = cmds;
	pid_t pid;

	// Parcourir chaque commande dans la liste
	while (current)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return;
		}

		if (pid == 0) // Processus enfant
		{
			char *cmd_path = get_cmd_path(current->cmd, env_array);
			if (cmd_path)
			{
				execve(cmd_path, current->args, env_array);
				perror("execve");
				free(cmd_path);
			}
			else
			{
				fprintf(stderr, "command not found: %s\n", current->cmd);
			}
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}

	current = cmds;
	while (current)
	{
		waitpid(current->pid, NULL, 0);
		current = current->next;
	}
}