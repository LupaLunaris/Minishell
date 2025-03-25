#include "../../includes/minishell.h"

//verifie si "l'argument" (splited_args[i]) est une redirection

int	is_redirect(char *token)
{
	return (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 ||
	ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0);
}
int	is_builtin(char *cmd)
{
	return (
		!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") ||
		!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "exit")
	);
}
// creer les node de la liste de commande en les initialisant
// je me pose la question de ce que doivent etre les node->... lier au redirection
// par default j'ai mis un *char "filname"
t_command	*create_cmd_node(void)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->builtin = 0;
	node->pid = 0;
	node->input_file = NULL;
	node->output_file = NULL;
	node->append = 0;
	node->heredoc = NULL;
	node->pipe_next = NULL;
	return (node);
}

// un lst_add_back mais avec t_command, rajoute un node a la fin de la liste

void	add_cmd_node(t_command **head, t_command *new_node)
{
	t_command   *current;

	current = create_cmd_node();
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->pipe_next)
		current = current->pipe_next;
	current->pipe_next = new_node;
}


// Compte le nombre d'arguments jusqu'au prochain pipe ou fin de tableau
int	count_args_to_pipe(char **splited_args, int start)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (splited_args[i] && ft_strcmp(splited_args[i], "|") != 0)
	{
		if (is_redirect(splited_args[i])) // on saute "l'argument" redirection
			i++;
		else
			count++; // on ne compte que les commandes
		i++;
	}
	return (count);
}

void	add_builtin(t_command *cmd)
{

	if (is_builtin(cmd->cmd))
	{
		cmd->builtin = 1;
	}
	while (cmd->pipe_next)
	{
		if (is_builtin(cmd->cmd))
		{
			cmd->builtin = 1;
		}

		cmd = cmd->pipe_next;
	}
}
