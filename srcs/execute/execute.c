/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:00:06 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/15 14:15:44 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int get_children(t_command *cmd)
{
	pid_t   wpid;
	int     status;
	int     save_status;

	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);  // Attendre un enfant
		if (wpid == -1 && errno == ECHILD)
			break; // Plus d'enfants à attendre
		while (cmd) // Parcourir les commandes pour vérifier leurs PIDs
		{
			if (wpid == cmd->pid)
				save_status = status;  // On sauvegarde le statut du processus associé
			cmd = cmd->next; // Passer à la commande suivante
		}
	}
	if (WIFSIGNALED(save_status))     // Si le processus enfant a été tué par un signal
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))  // Si le processus enfant s'est terminé normalement
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

static int create_children(t_command *cmd, t_env_list *env_list, t_shell_data *data)
{
	t_command *head = cmd;

	while (cmd)
	{
		pid_t pid = fork();
		if (pid == -1)
			return error_handler("fork", strerror(errno), 0, EXIT_FAILURE);
		cmd->pid = pid;
		if (pid == 0) // Enfant
		{
			setup_redirection(cmd->input_file, cmd->output_file, cmd->append);
			if (cmd->is_builtin)
				exit(execute_builtin(cmd, data));
			else
				execute_command(cmd, env_list);
		}
		cmd = cmd->next;
	}
	// Appeler get_children et enregistrer le statut dans data
	int status = get_children(head);
	data->exit_status = status;
	return (status);
}

/*vérifie si tout est en ordre avant l'exécution réelle d'une commande*/
static int prep_for_exec(t_command *cmd)
{
	if (!cmd)
		return (EXIT_SUCCESS); // Rien à faire s'il n'y a pas de commandes
	if (!cmd->cmd) // Pas de commande principale à exécuter
	{
		if (cmd->input_file || cmd->output_file)
		{
			if (check_redirections(cmd))
				return (EXIT_SUCCESS);
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	// Gérer les pipes si nécessaire
	if (!create_pipes(cmd))
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND); // Prêt à exécuter
}

int execute(t_command *cmd, t_env_list *env_list, t_shell_data *data)
{
	int ret;

	ret = prep_for_exec(cmd);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	// Si c'est une commande builtin et qu'elle n'est pas pipée
	if (!cmd->next && !cmd->prev && cmd->is_builtin)
	{
		setup_redirection(cmd->input_file, cmd->output_file, cmd->append);
		ret = execute_builtin(cmd, data); // Passer data au builtin
		restore_io(cmd->input_file, cmd->output_file);
		return (ret);
	}
	// Sinon, créer des enfants et passer data
	return (create_children(cmd, env_list, data));
}

