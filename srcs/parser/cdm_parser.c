#include "../../includes/minishell.h"

// Remplit les arguments de la commande
// splited_args est un array de *char issu du prompt de l'utilisateur
// donc tous ce qui est separer par un espace  y est stoker sous forme de *char
// pipe redirection cmd ...

//le principe de ce parsing est de tout stocker dans une listes *t_cmd

// chaque pipe ajoute un node a la liste

// chaque redirection rempli l'attribut correspondant dans le node courant

// si redirection < > << >>
//	 on stocke ce qui suit dans le node t_cdm courant
//  echo "bla" > test.txt
// cdm->args = {"echo", "bla"}
// cdm->output_file = test.txt
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

void	*clean_cmd_list(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->args)
			free_arr(head->args);
		free(head->input_file);
		free(head->output_file);
		free(head);
		head = tmp;
	}

	return (NULL);
}
int	process_redirection(t_cmd *current, char **splited_args, int *i)
{
	int one;
	int *isTrue;

	one = 1;
	isTrue = &one;

	if (!splited_args[*i])
		return (0);
	if (ft_strcmp(splited_args[*i], "<") == 0)
	{
		if (!splited_args[*i + 1]) // si il n'y a rien apres la redirection
			return (0); // mettre ceci dans une fonction a part avec message erreur : " zsh: parse error near `\n' " voir l'equivqlent bash
		current->input_file = ft_strdup(splited_args[++(*i)]); // stock le *char apres "<" dans le node courant
	}
	else if (ft_strcmp(splited_args[*i], ">") == 0)
	{
		if (!splited_args[*i + 1])
			return (0);
		current->output_file = ft_strdup(splited_args[++(*i)]);
	}
	else if (ft_strcmp(splited_args[*i], ">>") == 0)
	{
		if (!splited_args[*i + 1])
			return (0);
		current->output_file = ft_strdup(splited_args[++(*i)]);
		current->append = *isTrue;
	}
	else if (ft_strcmp(splited_args[*i], "<<") == 0)
	{
		if (!splited_args[*i + 1])
			return (0);
		current->heredoc = ft_strdup(splited_args[++(*i)]);
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






