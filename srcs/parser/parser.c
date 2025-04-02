/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:00:00 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/01 10:00:00 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_cmd	*curr;
	t_cmd	*tmp;

	curr = head;
	while (curr)
	{
		tmp = curr->next;
		if (curr->cmd)
			free(curr->cmd);
		if (curr->args)
			free_arr(curr->args);

		// Libérer les redirections
		t_redirection *redir_curr = curr->redirections;
		t_redirection *redir_tmp;
		while (redir_curr)
		{
			redir_tmp = redir_curr->next;
			if (redir_curr->file)
				free(redir_curr->file);
			if (redir_curr->heredoc_content)
				free(redir_curr->heredoc_content);
			free(redir_curr);
			redir_curr = redir_tmp;
		}

		free(curr);
		curr = tmp;
	}

	return (NULL);
}

/*
** Crée une nouvelle commande vide
*/
t_cmd *create_command(void)
{
	t_cmd *cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->pid = 0;
	cmd->is_builtin = 0;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	return (cmd);
}

/*
** Ajoute une redirection à une commande
*/
static int add_redirection(t_cmd *cmd, char *file, int type)
{
	t_redirection *new_redir;
	t_redirection *curr;

	new_redir = (t_redirection *)malloc(sizeof(t_redirection));
	if (!new_redir)
		return (0);
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
	{
		free(new_redir);
		return (0);
	}
	new_redir->type = type;
	new_redir->heredoc_content = NULL;
	new_redir->next = NULL;

	if (!cmd->redirections)
		cmd->redirections = new_redir;
	else
	{
		curr = cmd->redirections;
		while (curr->next)
			curr = curr->next;
		curr->next = new_redir;
	}
	return (1);
}

/*
** Compte le nombre d'arguments pour une commande (jusqu'au pipe suivant)
** en excluant les redirections et leurs fichiers
*/
static int count_args(t_token *token, t_token *end)
{
	int count;

	count = 0;
	while (token != end && token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
			count++;
		else if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT ||
				 token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
		{
			// Sauter le token de redirection et le nom de fichier
			token = token->next;
			if (!token)
				break;
		}
		token = token->next;
	}
	return (count);
}

/*
** Parse une commande simple (jusqu'au prochain pipe)
*/
static t_cmd *parse_command(t_token **token)
{
	t_cmd *cmd;
	int arg_count;
	int arg_index;

	if (!token || !*token)
		return (NULL);

	cmd = create_command();
	if (!cmd)
		return (NULL);

	// Compter le nombre d'arguments
	arg_count = count_args(*token, NULL);
	if (arg_count == 0)
	{
		// Pas d'arguments, juste des redirections peut-être
		cmd->args = (char **)malloc(sizeof(char *));
		if (!cmd->args)
		{
			free(cmd);
			return (NULL);
		}
		cmd->args[0] = NULL;
		arg_index = 0;
	}
	else
	{
		// Allouer le tableau d'arguments
		cmd->args = (char **)malloc(sizeof(char *) * (arg_count + 1));
		if (!cmd->args)
		{
			free(cmd);
			return (NULL);
		}
		arg_index = 0;
	}

	// Remplir le tableau d'arguments et traiter les redirections
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		if ((*token)->type == TOKEN_WORD)
		{
			// Ajouter à la liste des arguments
			cmd->args[arg_index] = ft_strdup((*token)->value);

			// Si c'est le premier argument, c'est la commande
			if (arg_index == 0)
				cmd->cmd = ft_strdup((*token)->value);

			arg_index++;
		}
		else if ((*token)->type == TOKEN_REDIR_IN || (*token)->type == TOKEN_REDIR_OUT ||
				 (*token)->type == TOKEN_APPEND || (*token)->type == TOKEN_HEREDOC)
		{
			int redir_type = 0;

			// Convertir le type de token en type de redirection
			if ((*token)->type == TOKEN_REDIR_IN)
				redir_type = REDIR_INPUT;
			else if ((*token)->type == TOKEN_REDIR_OUT)
				redir_type = REDIR_OUTPUT;
			else if ((*token)->type == TOKEN_APPEND)
				redir_type = REDIR_APPEND;
			else if ((*token)->type == TOKEN_HEREDOC)
				redir_type = REDIR_HEREDOC;

			// Passer au token suivant qui doit être le nom de fichier
			*token = (*token)->next;
			if (!*token || (*token)->type != TOKEN_WORD)
			{
				// Erreur: pas de nom de fichier après redirection
				ft_putendl_fd("minishell: syntax error near unexpected token", 2);
				free(cmd->cmd);
				free_arr(cmd->args);
				free(cmd);
				return (NULL);
			}

			// Ajouter la redirection
			if (!add_redirection(cmd, (*token)->value, redir_type))
			{
				free(cmd->cmd);
				free_arr(cmd->args);
				free(cmd);
				return (NULL);
			}
		}

		// Avancer au token suivant
		*token = (*token)->next;
	}

	// Marquer la fin du tableau d'arguments
	if (arg_count > 0)
		cmd->args[arg_index] = NULL;

	return (cmd);
}

/*
** Vérifie si une commande est un builtin
*/
static void check_builtins(t_cmd *cmd_list)
{
	t_cmd *cmd;

	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->cmd)
		{
			if (ft_strcmp(cmd->cmd, "echo") == 0 ||
				ft_strcmp(cmd->cmd, "cd") == 0 ||
				ft_strcmp(cmd->cmd, "pwd") == 0 ||
				ft_strcmp(cmd->cmd, "export") == 0 ||
				ft_strcmp(cmd->cmd, "unset") == 0 ||
				ft_strcmp(cmd->cmd, "env") == 0 ||
				ft_strcmp(cmd->cmd, "exit") == 0)
			{
				cmd->is_builtin = 1;
			}
		}
		cmd = cmd->next;
	}
}

/*
** Parse une liste de tokens en liste de commandes
*/
t_cmd *parse_tokens(t_token *tokens)
{
	t_cmd *cmd_list;
	t_cmd *current;
	t_token *token;

	if (!tokens)
		return (NULL);

	cmd_list = NULL;
	token = tokens;

	while (token)
	{
		// Parser une commande
		current = parse_command(&token);
		if (!current)
		{
			// Erreur pendant le parsing
			if (cmd_list)
				clean_cmd_list(cmd_list);
			return (NULL);
		}

		// Ajouter la commande à la liste
		if (!cmd_list)
			cmd_list = current;
		else
		{
			t_cmd *last = cmd_list;
			while (last->next)
				last = last->next;
			last->next = current;
			current->prev = last;
		}

		// Si on a atteint un pipe, avancer au token suivant
		if (token && token->type == TOKEN_PIPE)
			token = token->next;
	}

	// Identifier les builtins
	check_builtins(cmd_list);

	return (cmd_list);
}

/*
** Fonction principale de parsing
** Analyse l'entrée utilisateur et construit l'arbre de commandes
*/
t_cmd *parse_input(char *input)
{
	t_token *tokens;
	t_cmd *cmd_list;

	if (!input)
		return (NULL);

	// Lexing: convertir l'entrée en tokens
	tokens = lexer(input);
	if (!tokens)
		return (NULL);

	// Vérifier les erreurs de syntaxe
	t_token *current = tokens;
	while (current)
	{
		if (current->type == TOKEN_ERROR)
		{
			free_tokens(tokens);
			return (NULL);
		}
		current = current->next;
	}

	// Parsing: convertir les tokens en liste de commandes
	cmd_list = parse_tokens(tokens);

	// Libérer les tokens
	free_tokens(tokens);

	return (cmd_list);
}