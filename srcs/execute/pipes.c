/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:01:14 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/17 12:30:19 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Les pipes permettent de connecter plusieurs commandes 
 * ensemble (ex : ls | grep text | wc -l).
 */

 int	handle_pipes(t_command *cmd, char **envp) {
	int		fd[2]; // Tableau pour stocker les deux extrémités du pipe.
	pid_t	pid;
	if (pipe(fd) == -1)
	{ // Crée un pipe
		perror("Pipe failed");
		exit(EXIT_FAILURE);
	}
	if ((pid = fork()) == 0)
	{ // Processus enfant 1
		close(fd[0]); // Ferme la lecture du pipe
		dup2(fd[1], STDOUT_FILENO); // Redirige la sortie standard vers le pipe (écriture)
		close(fd[1]); // Ferme le descripteur inutile après dup2
		execve(cmd->cmd, cmd->args, envp); // Exécute la commande actuelle
		perror("Execution failed");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		close(fd[1]); // Ferme l'écriture du pipe dans le processus parent
		if (fork() == 0)
		{ // Processus enfant 2 : "command2"
			dup2(fd[0], STDIN_FILENO); // Redirige l'entrée standard depuis le pipe (lecture)
			close(fd[0]);
			execve(cmd->next->cmd, cmd->next->args, envp); // Exécute la commande suivante.
			perror("Execution failed");
			exit(EXIT_FAILURE);
		}
		else 
		{
			close(fd[0]); // Le processus parent ferme la lecture.
			wait(NULL); // Attend la fin de process1 et process2.
			wait(NULL);
		}
	}
	else
		perror("Fork failed"); // Échec du fork
	return (0);
}

