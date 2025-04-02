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

static void	manage_pipes(t_pipe_data *pd, int is_child)
{
	if (is_child)
	{
		if (pd->i > 0)
			dup2(pd->pipes[(pd->i - 1) % 2][0], STDIN_FILENO);
		if (pd->i < pd->cmd_count - 1)
			dup2(pd->pipes[pd->i % 2][1], STDOUT_FILENO);
		if (pd->pipes[0][0] != -1)
			close(pd->pipes[0][0]);
		if (pd->pipes[0][1] != -1)
			close(pd->pipes[0][1]);
		if (pd->pipes[1][0] != -1)
			close(pd->pipes[1][0]);
		if (pd->pipes[1][1] != -1)
			close(pd->pipes[1][1]);
	}
	else
	{
		if (pd->i > 0)
			close(pd->pipes[(pd->i - 1) % 2][0]);
		if (pd->i < pd->cmd_count - 1)
			close(pd->pipes[pd->i % 2][1]);
	}
}

static void	process_command(t_cmd *curr, t_shell_exec *se)
{
	char	**env_array;

	if (setup_redirection(curr->redirections) != 0)
		exit(EXIT_FAILURE);
	if (curr->is_builtin)
		exit(execute_builtin(curr, se->data));
	else
	{
		env_array = env_list_to_array(se->env_list);
		execute_command(curr, env_array);
	}
}

static int	create_process(t_cmd *curr, t_pipe_data *pd, t_shell_exec *se)
{
	pid_t	pid;

	if (pd->i < pd->cmd_count - 1 && pipe(pd->pipes[pd->i % 2]) == -1)
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
		manage_pipes(pd, 1);
		process_command(curr, se);
	}
	manage_pipes(pd, 0);
	return (pid);
}

static void	init_pipeline(t_pipe_data *pd, t_shell_exec *se,
		t_env_list *env_list, t_cmd *cmd_list)
{
	t_cmd	*curr;
	int		count;

	se->env_list = env_list;
	count = 0;
	curr = cmd_list;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	pd->cmd_count = count;
	pd->i = 0;
	pd->pipes[0][0] = -1;
	pd->pipes[0][1] = -1;
	pd->pipes[1][0] = -1;
	pd->pipes[1][1] = -1;
}

int execute_pipeline(t_cmd *cmd, t_env_list *env_list, t_shell_data *data)
{
    t_pipe_data     pd;
    t_cmd           *curr;
    t_shell_exec    se;
    int             status;
    int             last_status = 0;  // Pour stocker le statut de la dernière commande

    init_pipeline(&pd, &se, env_list, cmd);
    se.data = data;
    curr = cmd;
    while (curr)
    {
        curr->pid = create_process(curr, &pd, &se);
        if (curr->pid == -1)
            return (EXIT_FAILURE);
        curr = curr->next;
        pd.i++;
    }
    
    // Attendre toutes les commandes et obtenir le statut de la dernière
    curr = cmd;
    while (curr) {
        waitpid(curr->pid, &status, 0);
        if (WIFEXITED(status))
            last_status = WEXITSTATUS(status);
        curr = curr->next;
    }
    
    // Retourner le statut de la dernière commande
    return (last_status);
}
