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

static int	add_token_word(t_cmd *cmd, t_token **token, int index)
{
	int	arg_index;

	arg_index = index;
	if ((*token)->type == TOKEN_WORD)
	{
		cmd->args[arg_index] = ft_strdup((*token)->value);
		if (arg_index == 0)
			cmd->cmd = ft_strdup((*token)->value);
		arg_index++;
	}
	return (arg_index);
}

/*
** Parse une commande simple (jusqu'au prochain pipe)
*/
static t_cmd	*parse_command(t_token **token)
{
	t_cmd	*cmd;
	int		arg_count;
	int		arg_index;

	arg_index = 0;
	if (!token || !*token)
		return (NULL);
	cmd = create_command();
	if (!cmd)
		return (NULL);
	arg_count = count_args(*token, NULL);
	if (!(init_args(cmd, arg_count)))
		return (NULL);
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		arg_index = add_token_word(cmd, token, arg_index);
		if (!add_token_redir(cmd, token))
			return (NULL);
		*token = (*token)->next;
	}
	if (arg_count > 0)
		cmd->args[arg_index] = NULL;
	return (cmd);
}

/*
** Vérifie si une commande est un builtin
*/
static void	check_builtins(t_cmd *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->cmd)
		{
			if (ft_strcmp(cmd->cmd, "echo") == 0
				|| ft_strcmp(cmd->cmd, "cd") == 0
				|| ft_strcmp(cmd->cmd, "pwd") == 0
				|| ft_strcmp(cmd->cmd, "export") == 0
				|| ft_strcmp(cmd->cmd, "unset") == 0
				|| ft_strcmp(cmd->cmd, "env") == 0
				|| ft_strcmp(cmd->cmd, "exit") == 0)
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
t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current;
	t_token	*token;

	if (!tokens)
		return (NULL);
	cmd_list = NULL;
	token = tokens;
	while (token)
	{
		current = parse_command(&token);
		if (!current)
		{
			if (cmd_list)
				clean_cmd_list(cmd_list);
			return (NULL);
		}
		ft_cmdadd_back(&cmd_list, current);
		if (token && token->type == TOKEN_PIPE)
			token = token->next;
	}
	check_builtins(cmd_list);
	return (cmd_list);
}
/*
** Fonction principale de parsing
** Analyse l'entrée utilisateur et construit l'arbre de commandes
*/

t_cmd	*parse_input(char *input)
{
	t_token	*tokens;
	t_cmd	*cmd_list;
	t_token	*current;

	if (!input)
		return (NULL);
	tokens = lexer(input);
	if (!tokens)
		return (NULL);
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_ERROR)
		{
			free_tokens(tokens);
			return (NULL);
		}
		current = current->next;
	}
	cmd_list = parse_tokens(tokens);
	free_tokens(tokens);
	return (cmd_list);
}
