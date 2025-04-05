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
	int         count;
	t_env_list  *temp;
	char        **env_array;
	int			i;

	temp = env_list;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	i = 0;
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

int	has_redirections(t_cmd *cmd)
{
	return (cmd->redirections != NULL);
}

int	has_heredoc(t_cmd *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirections;	
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			return (1);
		redir = redir->next;
	}
	return (0);
}

static char *get_cmd_heredoc_content(t_cmd *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			return redir->heredoc_content;
		redir = redir->next;
	}
	return (NULL);
}

char *get_heredoc_delimiter(t_cmd *cmd)
{
	t_redirection *redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			return redir->file;
		redir = redir->next;
	}
	return (NULL);
}

int	get_children(t_cmd *cmd)
{
	t_cmd	*head = cmd;
	pid_t	wpid;
	int		status;
	int		save_status;

	status = 0;
	save_status = 0;
	while ((wpid = waitpid(-1, &status, 0)) > 0)
	{
		cmd = head;
		while (cmd)
		{
			if (wpid == cmd->pid)
			{
				save_status = status;
				break ;
			}
			cmd = cmd->next;
		}
	}
	if (WIFSIGNALED(save_status))
		return (128 + WTERMSIG(save_status));
	else if (WIFEXITED(save_status))
		return (WEXITSTATUS(save_status));
	else
		return (save_status);
}

int	create_children(t_cmd *cmd, t_env_list *env_list, t_shell_data *data)
{
	t_cmd	*head;
	char	**env_array;

	env_array = env_list_to_array(env_list);
	head = cmd;
	while (cmd)
	{
		pid_t pid = fork();
		if (pid == -1)
			return error_handler("fork", strerror(errno), 0, EXIT_FAILURE);
		cmd->pid = pid;
		if (pid == 0)
		{
			setup_redirection(cmd->redirections);
			if (cmd->is_builtin)
				exit(execute_builtin(cmd, data));
			else
				execute_command(cmd, env_array);
		}
		cmd = cmd->next;
	}
	int status = get_children(head);
	data->exit_status = status;
	return (status);
}

int	execute_builtin_cmd(t_cmd *cmd, t_shell_data *data)
{
	int	stdin_backup;
	int	stdout_backup;
	int	ret;

	stdin_backup = -1;
	stdout_backup = -1;
	if (has_redirections(cmd))
	{
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
	}
	setup_redirection(cmd->redirections);
	ret = execute_builtin(cmd, data);
	restore_io(stdin_backup, stdout_backup);
	return (ret);
}

int	execute(t_cmd *cmd, t_env_list *env_list, t_shell_data *data)
{
	t_cmd	*curr;
	int		status;

	curr = cmd;
	while (curr)
	{
		if (has_heredoc(curr))
		{
			char *delimiter = get_heredoc_delimiter(curr);
			if (delimiter && (!get_cmd_heredoc_content(curr) || 
				ft_strlen(get_cmd_heredoc_content(curr)) == 0))
			{
				status = process_heredoc(delimiter, curr);
				if (status != 0)
					return (status);
			}
		}
		curr = curr->next;
	}
	if (!cmd)
		return (EXIT_SUCCESS);
	if (cmd->next)
		return (execute_pipeline(cmd, env_list, data));
	if (cmd->is_builtin)
		return (execute_builtin_cmd(cmd, data));
	return (create_children(cmd, env_list, data));
}
