/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:51:39 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/30 14:51:39 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *create_cdm_path(char *cmd, char **paths)
{
    char *cmd_path;
    int i;

    i = 0;
    while (paths[i])
    {
        char *tmp = ft_strjoin(paths[i], "/");
        cmd_path = ft_strjoin(tmp, cmd);
        free(tmp);
        
        if (access(cmd_path, X_OK) == 0)
        {
            // On ne libère pas paths ici - c'est la responsabilité de l'appelant
            return cmd_path;
        }
        
        free(cmd_path);
        i++;
    }
    
    return NULL;
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

char *get_cmd_path(char *cmd, char **env_array)
{
    char *path;
    char **paths;
    struct stat file_stat;

    // Si la commande contient déjà un chemin
    if (strchr(cmd, '/'))
    {
        // On vérifie si le fichier existe et n'est pas un répertoire
        if (access(cmd, F_OK) == 0)
        {
            if (stat(cmd, &file_stat) == 0 && !S_ISDIR(file_stat.st_mode))
                return ft_strdup(cmd);
        }
        return NULL;
    }

    // Sinon, on cherche dans PATH
    path = get_path(env_array);
    if (!path)
        return NULL;
    
    paths = ft_split(path, ':');
    if (!paths)
        return NULL;
    
    char *cmd_path = create_cdm_path(cmd, paths);
    if (cmd_path)
    {
        // Vérifier que ce n'est pas un répertoire
        if (stat(cmd_path, &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
        {
            free(cmd_path);
            free_arr(paths);
            return NULL;
        }
        return cmd_path;
    }
    
    free_arr(paths);
    return NULL;
}


int execute_command_for_heredoc(t_cmd *cmd, char **env_array)
{
    char    *cmd_path;
    
    cmd_path = get_cmd_path(cmd->cmd, env_array);
    if (!cmd_path)
    {
        fprintf(stderr, "command not found: %s\n", cmd->cmd);
        return EXIT_FAILURE;
    }
    
    execve(cmd_path, cmd->args, env_array);
    perror("execve");
    free(cmd_path);
    return EXIT_FAILURE;
}

void execute_command(t_cmd *cmd, char **env_array)
{
    char *cmd_path;
    struct stat file_stat;

	if (cmd->cmd && 
        ((cmd->cmd[0] == '$' && cmd->cmd[1] == '\0') || 
         (cmd->cmd[0] == '$' && cmd->cmd[1] == '?' && cmd->cmd[2] == '\0')))
    	{
        	error_handler(cmd->cmd, "command not found", 1, 127);
       		exit(127);
    	}
    // Cas où la commande contient un chemin (absolu ou relatif)
    if (strchr(cmd->cmd, '/'))
    {
        // Vérifier si le fichier existe
        if (access(cmd->cmd, F_OK) != 0)
        {
            error_handler(cmd->cmd, "No such file or directory", 1, 127);
            exit(127);
        }
        // Vérifier les statistiques du fichier
        if (stat(cmd->cmd, &file_stat) == 0)
        {
            // Vérifier si c'est un répertoire
            if (S_ISDIR(file_stat.st_mode))
            {
                error_handler(cmd->cmd, "Is a directory", 1, 126);
                exit(126);
            }
            // Vérifier les permissions d'exécution
            if (access(cmd->cmd, X_OK) != 0)
            {
                error_handler(cmd->cmd, "Permission denied", 1, 126);
                exit(126);
            }
        }
        
        // Si on arrive ici, on essaie d'exécuter
        execve(cmd->cmd, cmd->args, env_array);
        // Si execve retourne, c'est une erreur
        error_handler(cmd->cmd, "Error executing command", 1, 126);
        exit(126);
    }
    // Cas où la commande doit être cherchée dans le PATH
    else
    {
        cmd_path = get_cmd_path(cmd->cmd, env_array);
        if (cmd_path)
        {
            execve(cmd_path, cmd->args, env_array);
            free(cmd_path);
            // Si execve retourne, c'est une erreur
            error_handler(cmd->cmd, "Error executing command", 1, 126);
            exit(126);
        }
        else
        {
            error_handler(cmd->cmd, "command not found", 1, 127);
            exit(127);
        }
    }
}
