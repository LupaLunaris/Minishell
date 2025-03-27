/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pipes.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: Jpaulis <Jpaulis@student.s19.be>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 18:01:14 by Jpaulis		   #+#	#+#			 */
/*   Updated: 2025/03/19 17:34:36 by Jpaulis		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"


/* Configure l'entrée/sortie pour un processus enfant dans un pipeline */
	// Connecter l'entrée standard au pipe précédent (sauf pour la première commande)
	// Connecter la sortie standard au pipe actuel (sauf pour la dernière commande)
	// Fermer tous les descripteurs de pipe

	static void setup_child_pipes(int pipes[2][2], int i, int cmd_count)
	{
		// Rediriger l'entrée standard depuis le pipe précédent (sauf pour la première commande)
		if (i > 0)
		{
			dup2(pipes[(i - 1) % 2][0], STDIN_FILENO);
		}
		
		// Rediriger la sortie standard vers le pipe actuel (sauf pour la dernière commande)
		if (i < cmd_count - 1)
		{
			dup2(pipes[i % 2][1], STDOUT_FILENO);
		}
		
		// IMPORTANT: Fermer TOUS les descripteurs de pipe non utilisés
		// Cela est crucial pour éviter les blocages
		if (pipes[0][0] != -1) close(pipes[0][0]);
		if (pipes[0][1] != -1) close(pipes[0][1]);
		if (pipes[1][0] != -1) close(pipes[1][0]);
		if (pipes[1][1] != -1) close(pipes[1][1]);
	}
	

/* Gère les descripteurs de pipe dans le processus parent */
	// Fermer les pipes dans le parent après usage
static void	close_parent_pipes(int pipes[2][2], int i, int cmd_count)
{
	if (i > 0)
		close(pipes[(i - 1) % 2][0]);
	if (i < cmd_count - 1)
		close(pipes[i % 2][1]);
}

/* Exécute la commande dans un processus enfant */
static void execute_child_process(t_cmd *curr, t_env_list *env_list, t_shell_data *data)
{
    // Appliquer les redirections après la configuration des pipes
    // Si la commande a des redirections, elles doivent avoir priorité sur les pipes
    if (check_redirections(curr) != 0)
        exit(EXIT_FAILURE);
        
    if (curr->is_builtin)
        exit(execute_builtin(curr, data));
    else
    {
        char **env_array = env_list_to_array(env_list);
        execute_command(curr, env_array);
    }
}


/* Compte le nombre de commandes dans le pipeline */
static int	count_commands(t_cmd *cmd)
{
	int count = 0;
	t_cmd *curr = cmd;

	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return count;
}

static int	prepare_cmd_process(t_cmd *curr, int pipes[2][2], int i, int cmd_count,
	t_env_list *env_list, t_shell_data *data)
{

	if (i < cmd_count - 1 && pipe(pipes[i % 2]) == -1) // Créer un pipe si ce n'est pas la dernière commande
	{
		perror("pipe");
		return -1;
	}
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return -1;
	}
	if (pid == 0) // Processus enfant
	{
		setup_child_pipes(pipes, i, cmd_count);
		execute_child_process(curr, env_list, data);
	}
	close_parent_pipes(pipes, i, cmd_count);// Processus parent
	return pid;
}

/* Exécute une séquence de commandes reliées par des pipes */
int execute_pipeline(t_cmd *cmd, t_env_list *env_list, t_shell_data *data)
{
    int     pipes[2][2]; // Tableau pour stocker deux jeux de descripteurs de pipe
    int     cmd_count;
    int     i;
    pid_t   pid;
    t_cmd   *curr;
    int     status = 0;
    
    cmd_count = count_commands(cmd);
    curr = cmd;
    i = 0;
    
    // D'abord, vider et initialiser les pipes
    pipes[0][0] = -1; pipes[0][1] = -1;
    pipes[1][0] = -1; pipes[1][1] = -1;
    
    while (curr)
    {
        pid = prepare_cmd_process(curr, pipes, i, cmd_count, env_list, data);
        if (pid == -1)
            return EXIT_FAILURE;
            
        // Stocker le PID dans la structure cmd pour référence future
        curr->pid = pid;
        
        curr = curr->next;
        i++;
    }
    
    // Attendre que tous les processus enfants se terminent
    // et récupérer le statut du dernier pour le retourner
    while (wait(&status) > 0)
        ;
    
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return EXIT_FAILURE;
}

/*
pour mettre au norme utiliser t_shell_exec
*/

// typedef struct s_shell_exec
// {
// 	t_env_list	*env_list;
// 	t_shell_data	*data;
// }	t_s

// static int	prepare_process(t_cmd *curr, int pipes[2][2], int *vars,
// 	t_shell_exec *se)
// {
// 	pid_t	pid;
// 	int		i;
// 	int		cmd_count;

// 	i = vars[0];
// 	cmd_count = vars[1];
// 	if (i < cmd_count - 1 && pipe(pipes[i % 2]) == -1)
// 	{
// 		perror("pipe");
// 		return (-1);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		return (-1);
// 	}
// 	if (pid == 0)
// 	{
// 		setup_child_pipes(pipes, i, cmd_count);
// 		execute_child_process(curr, se->env_list, se->data);
// 	}
// 		close_parent_pipes(pipes, i, cmd_count);
// 	return (pid);
// }

// /* Exécute une séquence de commandes reliées par des pipes */
// int	execute_pipeline(t_cmd *cmd, t_env_list *env_list, t_shell_data *data)
// {
// 	int			pipes[2][2];
// 	int			vars[2];
// 	pid_t		pid;
// 	t_cmd		*curr;
// 	t_shell_exec	se;

// 	se.env_list = env_list;
// 	se.data = data;
// 	vars[1] = count_commands(cmd);
// 	curr = cmd;
// 	vars[0] = 0;
// 	while (curr)
// 	{
// 		pid = prepare_process(curr, pipes, vars, &se);
// 		if (pid == -1)
// 			return (EXIT_FAILURE);
// 		curr->pid = pid;
// 		curr = curr->next;
// 		vars[0]++;
// 	}
// 	return (get_children(cmd));
// }