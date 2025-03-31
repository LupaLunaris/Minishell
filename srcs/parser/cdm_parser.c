#include "../../includes/minishell.h"

void	free_arr(char **arr)
{
	int  i;

	i = 0;
	if (!arr)
		return;
	while(arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}

void clean_redirections(t_redirection *head)
{
    t_redirection *tmp;

    while (head)
    {
        tmp = head->next;
        free(head->file);
        free(head->heredoc_content);
        free(head);
        head = tmp;
    }
}

void *clean_cmd_list(t_cmd *head)
{
    t_cmd *tmp;

    while (head)
    {
        tmp = head->next;
        if (head->args)
            free_arr(head->args);
        clean_redirections(head->redirections); // Nettoyer les redirections
        free(head);
        head = tmp;
    }
    return (NULL);
}

// Fonction auxiliaire pour ajouter une redirection à la liste
void add_redirection(t_cmd *cmd, char *file, int type, char *heredoc_content)
{
    t_redirection *new_redir = malloc(sizeof(t_redirection));
    if (!new_redir)
        return; // À gérer : erreur d'allocation
    
    new_redir->file = file ? ft_strdup(file) : NULL;
    new_redir->type = type;
    new_redir->heredoc_content = heredoc_content ? ft_strdup(heredoc_content) : NULL;
    new_redir->next = NULL;
    
    // Ajouter la nouvelle redirection à la fin de la liste
    if (!cmd->redirections)
    {
        cmd->redirections = new_redir;
    }
    else
    {
        t_redirection *curr = cmd->redirections;
        while (curr->next)
            curr = curr->next;
        curr->next = new_redir;
    }
}

int process_redirection(t_cmd *current, char **splited_args, int *i)
{
    if (!splited_args[*i])
        return (0);
        
    if (ft_strcmp(splited_args[*i], "<") == 0)
    {
        if (!splited_args[*i + 1])
            return (0); // Erreur de syntaxe
        
        add_redirection(current, splited_args[++(*i)], REDIR_INPUT, NULL);
    }
    else if (ft_strcmp(splited_args[*i], ">") == 0)
    {
        if (!splited_args[*i + 1])
            return (0);
            
        add_redirection(current, splited_args[++(*i)], REDIR_OUTPUT, NULL);
    }
    else if (ft_strcmp(splited_args[*i], ">>") == 0)
    {
        if (!splited_args[*i + 1])
            return (0);
            
        add_redirection(current, splited_args[++(*i)], REDIR_APPEND, NULL);
    }
    else if (ft_strcmp(splited_args[*i], "<<") == 0)
    {
        if (!splited_args[*i + 1])
            return (0);
            
        // Pour le heredoc, tu dois gérer le contenu séparément
        // Ici je suppose que tu as une fonction pour lire le heredoc
        char *heredoc_content = get_heredoc_content(splited_args[++(*i)]);
        add_redirection(current, NULL, REDIR_HEREDOC, heredoc_content);
        free(heredoc_content); // Libérer la copie temporaire
    }
    return (1);
}


//fill_cmd_args parcour le tableau splited_args en etant appeler par parser
//si l'argument est un pipe il gere la redirection et stock la *char "cdm arg1 arg2" dans cdm ->args


void	fill_cmd_args(t_cmd *cmd, char **splited_args, int *i)
{
	int	arg_count;
	int	arg_idx;

	arg_count = count_args_to_pipe(splited_args, *i);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return ;
	arg_idx = 0;
	while (splited_args[*i] && ft_strcmp(splited_args[*i], "|") != 0)
	{
		if (is_redirect(splited_args[*i]))
		{
			process_redirection(cmd, splited_args, i);
			(*i)++;
		}
		else
		{
			cmd->args[arg_idx++] = ft_strdup(splited_args[*i]);
			(*i)++;
		}
	}
	cmd->args[arg_idx] = NULL;
}

// parser fait la liste t_cmd a partit de splited_args

t_cmd	*parser(char **splited_args)
{
	t_cmd   *head;
	t_cmd   *current;
	int	 i;
	if(!splited_args)
		return (NULL);
	head = NULL;
	i = 0;
	while (splited_args[i])
	{
		current = create_cmd_node();
		if (splited_args[i])
			current->cmd = ft_strdup(splited_args[i]);
		if (!current)
			return (clean_cmd_list(head));
		fill_cmd_args(current, splited_args, &i);
		if (splited_args[i] && ft_strcmp(splited_args[i], "|") == 0) // tant qu'on est pas sur un pipe on avance jusqu'a la fin
			i++;
		add_cmd_node(&head, current); // le node current (new_node) reste null si pas de pipe
									 // voir la fonction dans parser utils -> le current remplis par fill_cmd_args devient le head dans ce cas.
	}
	return (head);
}
