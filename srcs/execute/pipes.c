/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:01:14 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/19 17:34:36 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* setup_pipes:
 * Configure les entrées/sorties des pipes pour une commande
 */
 void setup_pipes(t_cmd *cmd_list, t_cmd *curr)
 {
	 if (!curr)
		 return;
	 printf("on entre dans la fonction setup_pipe\n");
	 // Si commande précédente existe et a un pipe, connecter son pipe à l'entrée
	 printf("curr->inputfile %s\n",curr->input_file);
	 if (curr->prev && curr->pipe_fd[0] != -1 ) //&& !curr->input_file
	 {
		 printf("un pipe précédente existe\n");
		 dup2(curr->prev->pipe_fd[0], STDIN_FILENO);
		 //printf("un pipe précédente existe\n");
	 }
	 // Si pipé à une commande suivante, connecter sa sortie au pipe
	 if (curr->next && curr->pipe_fd[1] != -1) // && !curr->output_file
	 {
		 printf("un pipe suivant existe\n");
		 dup2(curr->pipe_fd[1], STDOUT_FILENO);
		 //printf("un pipe suivant existe\n");
	 }
	 printf("on sort des verifs la fonction setup_pipe\n");

	 // Fermer tous les pipes inutiles
	t_cmd *tmp = cmd_list;
	while (tmp)
    {
        if (tmp->pipe_fd[0] != -1 &&
            (tmp != curr || (curr->prev && curr->prev->pipe_fd[0] != curr->pipe_fd[0])))
			{
				printf("on a fermer le pipes fd[0] de la fonction setup_pipe\n");
				close(tmp->pipe_fd[0]);
			}

        if (tmp->pipe_fd[1] != -1 &&
            (tmp != curr || (curr->next && curr->next->pipe_fd[1] != curr->pipe_fd[1])))
			{
				printf("on a fermer le pipes fd[1] de la fonction setup_pipe\n");
				close(tmp->pipe_fd[1]);
			}
        tmp = tmp->next;
    }
}

/* create_pipes:
 * Crée les pipes pour les commandes chaînées
 */
bool create_pipes(t_cmd *cmd_list)
{
    t_cmd *curr = cmd_list;
	//printf("un pipe est creer\n");
    while (curr)
    {
        curr->pipe_fd[0] = -1;
        curr->pipe_fd[1] = -1;

        // Crée un pipe si nécessaire (s'il y a une commande suivante)
        if (curr->next)
        {
            if (pipe(curr->pipe_fd) == -1)
            {
                perror("pipe");
                return false;
            }
			printf("un pipe est creer dans la fonction create_pipe\n");
        }
        curr = curr->next;
    }
    return true;
}

/* close_all_pipes:
 * Ferme tous les pipes
 */
static void close_all_pipes(t_cmd *cmd_list)
{
    t_cmd *curr = cmd_list;

    while (curr)
    {
        if (curr->pipe_fd[0] != -1)
            close(curr->pipe_fd[0]);
        if (curr->pipe_fd[1] != -1)
            close(curr->pipe_fd[1]);
        curr = curr->next;
    }
}

/* execute_piped_cmd:
 * Exécute une commande dans un pipeline
 */
static void execute_piped_cmd(t_cmd *cmd, t_cmd *cmd_list,
                            t_env_list *env_list, t_shell_data *data)
{

	char **env_array = env_list_to_array(env_list);
	// Configure les redirections et pipes
	printf("on entre dans une commande pipe dans excecute_pipe_cdm\n");
    setup_redirection(cmd->input_file, cmd->output_file, cmd->append);

    setup_pipes(cmd_list, cmd);

    // Exécute la commande
    if (cmd->is_builtin)
    {
        int status = execute_builtin(cmd, data);
        exit(status);
    }
    else
    {
        printf("on entre dans une commande pipe dans excecute_pipe_cdm\n");
		execute_command(cmd, env_array);
        // execute_command appelle déjà exit en interne si nécessaire
    }
}

/* execute_pipeline:
 * Exécute une série de commandes liées par des pipes
 */
int execute_pipeline(t_cmd *cmd, t_env_list *env_list, t_shell_data *data)
{
    bool has_pipe = false;
    t_cmd *curr = cmd;

    // Vérifie si une commande dans la liste est reliée par pipe
    while (curr)
    {
        if (curr->next)
        {
            has_pipe = true;
            break;
        }
        curr = curr->next;
    }

    // Si pas de pipe et builtin, exécution directe
    if (!has_pipe && cmd->is_builtin)
    {
        setup_redirection(cmd->input_file, cmd->output_file, cmd->append);
        int status = execute_builtin(cmd, data);
        restore_io(cmd->input_file, cmd->output_file);
        return status;
    }

    // Crée les pipes nécessaires
    if (!create_pipes(cmd))
        return EXIT_FAILURE;

    // Crée un processus pour chaque commande
    curr = cmd;
    while (curr)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            close_all_pipes(cmd);
            return EXIT_FAILURE;
        }

        if (pid == 0) // Processus enfant
		{
			printf("on creer des processecus dans execute_pipeline\n");
			execute_piped_cmd(curr, cmd, env_list, data);
			printf("on sort de execute_piped_cmd vers execute_pipeline\n");
		}


        curr->pid = pid;
        curr = curr->next;
    }

    // Ferme tous les pipes dans le processus parent
    close_all_pipes(cmd);

    // Attendre la fin des processus enfants
    return get_children(cmd);
	return 0;
}
