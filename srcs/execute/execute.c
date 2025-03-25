/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   execute.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: Jpaulis <Jpaulis@student.s19.be>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 18:00:06 by Jpaulis		   #+#	#+#			 */
/*   Updated: 2025/03/19 17:34:15 by Jpaulis		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

char	**env_list_to_array(t_env_list *env_list)
{
	int count = 0;
	t_env_list *temp = env_list;

	while (temp)
	{
		count++;
		temp = temp->next;
	}

	char **env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);

	int i = 0;
	temp = env_list;
	while (temp)
	{
		env_array[i] = ft_strjoin_env(temp->key, temp->value);
		temp = temp->next;
		i++;
	}
	env_array[i] = NULL;

	return (env_array);
}

int get_children(t_cmd *cmd)
{
	pid_t   wpid;
	int	 status;
	int	 save_status;

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
	if (WIFSIGNALED(save_status))	 // Si le processus enfant a été tué par un signal
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))  // Si le processus enfant s'est terminé normalement
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

int create_children(t_cmd *cmd, t_env_list *env_list, t_shell_data *data)
{
	t_cmd *head = cmd;
	char **env_array = env_list_to_array(env_list);

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
				execute_command(cmd, env_array);
		}
		cmd = cmd->next;
	}
	// Appeler get_children et enregistrer le statut dans data
	int status = get_children(head);
	data->exit_status = status;
	return (status);
}

// /*vérifie si tout est en ordre avant l'exécution réelle d'une commande*/
// static int prep_for_exec(t_cmd *cmd)
// {
// 	if (!cmd)
// 		return (EXIT_SUCCESS); // Rien à faire s'il n'y a pas de commandes
// 	if (!cmd->cmd) // Pas de commande principale à exécuter
// 	{
// 		if (cmd->input_file || cmd->output_file)
// 		{
// 			if (check_redirections(cmd))
// 				return (EXIT_SUCCESS);
// 			return (EXIT_FAILURE);
// 		}
// 		return (EXIT_SUCCESS);
// 	}
// 	// Gérer les pipes si nécessaire
// 	if (!create_pipes(cmd))
// 		return (EXIT_FAILURE);
// 	return (CMD_NOT_FOUND); // Prêt à exécuter
// }

int execute(t_cmd *cmd, t_env_list *env_list, t_shell_data *data)
{
	int ret;

	if (!cmd)
		return EXIT_SUCCESS;
	// Vérifie si la commande est valide et gère les redirections simples

	printf("cmd = %s\n",cmd->cmd);
	printf("is_builtin = %d\n",cmd->is_builtin);

	if (!cmd->cmd)
	{
		if (cmd->input_file || cmd->output_file)
		{
			if (check_redirections(cmd))
				return EXIT_SUCCESS;
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	// Vérifie s'il y a des pipes dans la chaîne de commandes
	t_cmd *curr = cmd;
	bool has_pipe = false;
	while (curr->next)
	{
		has_pipe = true;
		printf("is pipe\n");
		break;
	}

	// Si on a des pipes, utilise execute_pipeline
	if (has_pipe)
		return execute_pipeline(cmd, env_list, data);
	// Si c'est une commande builtin sans pipe
	if (cmd->is_builtin)
	{
		printf("on rentre dans la boucle is builtin\n");
		setup_redirection(cmd->input_file, cmd->output_file, cmd->append);
		ret = execute_builtin(cmd, data);
		restore_io(cmd->input_file, cmd->output_file);
		return ret;
	}
	// Pour les commandes externes sans pipe
	return create_children(cmd, env_list, data);
}

