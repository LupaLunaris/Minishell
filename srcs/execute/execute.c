/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:00:06 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/22 13:22:03 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int get_children(t_command *cmd)
{
	pid_t wpid;
	int status;
	int save_status;

	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == cmd->pid)
			save_status = status;
		continue;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

static int create_children(t_command *cmd, t_env_list *env_list)
{
	while (cmd)
	{
		pid_t pid = fork();
		if (pid == -1) //si le fork a échoué
			return error_handler("fork", strerror(errno), 0, EXIT_FAILURE);
		else if (pid == 0)
		{
			// Dans le processus enfant
			setup_redirection(cmd->input_file, cmd->output_file, cmd->append);
			if (cmd->is_builtin)
				exit(execute_builtin(cmd, env_list)); // Exécuter le builtin dans l'enfant
			else
				execute_command(cmd, env_list); // Exécuter une commande normale
		}
		cmd = cmd->next;
	}
	return (get_children(cmd));
}

/*vérifie si tout est en ordre avant l'exécution réelle d'une commande*/
static int prep_for_exec(t_command *cmd)
{
	if (!cmd) // Pas de commandes à exécuter
		return (EXIT_SUCCESS);
	if (!cmd->cmd)
	{
		if (cmd->input_file || cmd->output_file)
		{
			// Vérifie redirections input/output
			if (!setup_redirection(cmd->input_file, cmd->output_file, cmd->append))
				return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	if (cmd->next != NULL) // Si plusieurs commandes, prépare les pipes
	{
		if (!handle_pipes(cmd, cmd->args))
			return (EXIT_FAILURE);
	}
	return (CMD_NOT_FOUND);
}

int execute(t_command *cmd, t_env_list *env_list)
{
	int ret;

	ret = prep_for_exec(cmd);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	if (!cmd->next && cmd->is_builtin) // Pas de pipe, un seul builtin
		return (execute_builtin(cmd, env_list));
	return (create_children(cmd, env_list));
}
