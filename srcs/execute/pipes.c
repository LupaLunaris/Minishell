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

static void	setup_child_pipes(int pipes[2][2], int i, int cmd_count)
{
	if (i > 0)
		dup2(pipes[(i - 1) % 2][0], STDIN_FILENO);
	if (i < cmd_count - 1)
		dup2(pipes[i % 2][1], STDOUT_FILENO);
	if (pipes[0][0] != -1)
		close(pipes[0][0]);
	if (pipes[0][1] != -1)
		close(pipes[0][1]);
	if (pipes[1][0] != -1)
		close(pipes[1][0]);
	if (pipes[1][1] != -1)
		close(pipes[1][1]);
}

/* Gère les descripteurs de pipe dans le processus parent */
static void	close_parent_pipes(int pipes[2][2], int i, int cmd_count)
{
	if (i > 0)
		close(pipes[(i - 1) % 2][0]);
	if (i < cmd_count - 1)
		close(pipes[i % 2][1]);
}

/* Exécute la commande dans un processus enfant */
static void	execute_child_process(t_cmd *curr, t_env_list *env_list,
	t_shell_data *data)
{
	char	**env_array;

	if (check_redirections(curr) != 0)
		exit(EXIT_FAILURE);
	if (curr->is_builtin)
		exit(execute_builtin(curr, data));
	else
	{
		env_array = env_list_to_array(env_list);
		execute_command(curr, env_array);
	}
}

/* Compte le nombre de commandes dans le pipeline */
static int	count_commands(t_cmd *cmd)
{
	int		count;
	t_cmd	*curr;

	count = 0;
	curr = cmd;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

static int	prepare_cmd_process(t_cmd *curr, int pipes[2][2], int i, int cmd_count,
	t_env_list *env_list, t_shell_data *data)
{
	pid_t	pid;

	if (i < cmd_count - 1 && pipe(pipes[i % 2]) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		setup_child_pipes(pipes, i, cmd_count);
		execute_child_process(curr, env_list, data);
	}
	close_parent_pipes(pipes, i, cmd_count);
	return (pid);
}

/* Exécute une séquence de commandes reliées par des pipes */
int	execute_pipeline(t_cmd *cmd, t_env_list *env_list, t_shell_data *data)
{
	int		pipes[2][2];
	int		cmd_count;
	int		i;
	pid_t	pid;
	t_cmd	*curr;
	int		status;

	cmd_count = count_commands(cmd);
	curr = cmd;
	i = 0;
	status = 0;
	pipes[0][0] = -1;
	pipes[0][1] = -1;
	pipes[1][0] = -1;
	pipes[1][1] = -1;
	while (curr)
	{
		pid = prepare_cmd_process(curr, pipes, i, cmd_count, env_list, data);
		if (pid == -1)
			return (EXIT_FAILURE);
		curr->pid = pid;
		curr = curr->next;
		i++;
	}
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
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