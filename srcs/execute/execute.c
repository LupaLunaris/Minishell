/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:00:06 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/20 15:31:54 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
/** Cette fonction vérifie qu'il s'agit d'un builtin.
  * Elle configure redirections et pipes 
  * avant d'exécuter les commandes avec execve
  **/
int execute_command(t_command *cmd, char **envp)
{
	if (!cmd) // Si la commande est NULL, on ne fait rien.
		return;
	if (is_builtin(cmd->cmd))
	{  // Si c'est un **builtin**, on l'exécute directement.
		execute_builtin(cmd, envp); // Les builtins comme `echo`, `cd`, `env`, etc.
		return;
	}
	if (cmd->input_file || cmd->output_file) // Si la commande contient une redirection :
		setup_redirection(cmd->input_file, cmd->output_file, cmd->append); // Configure les entrées/sorties pour les redirections
	if (cmd->next) // Si cette commande est suivie d'une autre (pipeline logique) :
		handle_pipes(cmd, envp); // Gère les **pipes** entre cette commande et la suivante.
	else
	{ // Exécution d'une commande simple (pas de pipeline impliqué ici)
		pid_t pid = fork(); // Crée un processus enfant.
		if (pid == 0)
		{ // Processus enfant
			execve(cmd->cmd, cmd->args, envp); // Exécute la commande avec environment variables.
			perror("Execution failed"); // Si execve échoue, on log une erreur.
			exit(EXIT_FAILURE);   // Quitte en cas d'erreur.
		}
		else if (pid > 0) // Processus parent
			waitpid(pid, NULL, 0);  // Attend que l'enfant termine avant de continuer.
		else
			perror("Fork failed");  // Erreur lors de la création du processus enfant.
	}
	return(0);
}
