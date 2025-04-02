/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:08:00 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 14:08:00 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Vérifie si un caractère est un opérateur */
int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';');
}

/* Vérifie si un caractère est un espace */
int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/* Crée un nouveau token */
t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

/* Ajoute un token à la liste */
void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!tokens || !new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

/* Libère la mémoire utilisée par les tokens */
void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

/* Initialise la structure du lexer */
static void	init_lexer(t_lexer *lex, char *input)
{
	lex->input = input;
	lex->position = 0;
	lex->current_token = malloc(4096);
	if (!lex->current_token)
		return ;
	lex->current_pos = 0;
	lex->tokens = NULL;
	lex->state = STATE_NORMAL;
}

/* Finalise le token courant et l'ajoute à la liste */
static void	add_current_token(t_lexer *lex)
{
	if (lex->current_pos > 0)
	{
		lex->current_token[lex->current_pos] = '\0';
		add_token(&lex->tokens, create_token(lex->current_token, TOKEN_WORD));
		lex->current_pos = 0;
	}
}

/* Gère une redirection de type input (<, <<) */
static void handle_input_redirection(t_lexer *lex)
{
	if (lex->input[lex->position + 1] == '<')
	{
		add_token(&lex->tokens, create_token("<<", TOKEN_HEREDOC));
		lex->position += 2;
	}
	else
	{
		add_token(&lex->tokens, create_token("<", TOKEN_REDIR_IN));
		lex->position++;
	}
}

/* Gère une redirection de type output (>, >>) */
static void handle_output_redirection(t_lexer *lex)
{
	if (lex->input[lex->position + 1] == '>')
	{
		add_token(&lex->tokens, create_token(">>", TOKEN_APPEND));
		lex->position += 2;
	}
	else
	{
		add_token(&lex->tokens, create_token(">", TOKEN_REDIR_OUT));
		lex->position++;
	}
}

/* Gère un opérateur de redirection */
static void handle_redirection(t_lexer *lex)
{
	add_current_token(lex);

	if (lex->input[lex->position] == '<')
		handle_input_redirection(lex);
	else if (lex->input[lex->position] == '>')
		handle_output_redirection(lex);
}

/* Gère un pipe */
static void	handle_pipe(t_lexer *lex)
{
	add_current_token(lex);
	add_token(&lex->tokens, create_token("|", TOKEN_PIPE));
	lex->position++;
}

/* Gère un guillemet simple ou double */
static void handle_quote(t_lexer *lex, char quote_type)
{
	// On ajoute le guillemet ouvrant au token
	lex->current_token[lex->current_pos++] = quote_type;
	lex->position++;

	// Changement d'état selon le type de guillemet
	if (quote_type == '\'')
		lex->state = STATE_IN_SQUOTE;
	else if (quote_type == '"')
		lex->state = STATE_IN_DQUOTE;
}

/* Gère un caractère normal (ni espace, ni opérateur, ni guillemet) */
static void handle_normal_char(t_lexer *lex)
{
	lex->current_token[lex->current_pos++] = lex->input[lex->position];
	lex->position++;
}

/* Gère l'état normal (hors guillemets) */
static void process_normal_state(t_lexer *lex)
{
	char c;

	c = lex->input[lex->position];

	if (is_space(c))
	{
		add_current_token(lex);
		lex->position++;
	}
	else if (c == '<' || c == '>')
		handle_redirection(lex);
	else if (c == '|')
		handle_pipe(lex);
	else if (c == '\'' || c == '"')
		handle_quote(lex, c);
	else
		handle_normal_char(lex);
}

/* Gère l'état dans des guillemets simples */
static void	process_squote_state(t_lexer *lex)
{
	char	c;

	c = lex->input[lex->position];

	lex->current_token[lex->current_pos++] = c;
	lex->position++;

	if (c == '\'')
		lex->state = STATE_NORMAL;
}

/* Gère l'état dans des guillemets doubles */
static void	process_dquote_state(t_lexer *lex)
{
	char	c;

	c = lex->input[lex->position];

	lex->current_token[lex->current_pos++] = c;
	lex->position++;

	if (c == '"')
		lex->state = STATE_NORMAL;
}

/* Fonction principale de lexing */
t_token	*lexer(char *input)
{
	t_lexer	lex;

	if (!input)
		return (NULL);

	init_lexer(&lex, input);
	if (!lex.current_token)
		return (NULL);

	while (lex.input[lex.position])
	{
		if (lex.state == STATE_NORMAL)
			process_normal_state(&lex);
		else if (lex.state == STATE_IN_SQUOTE)
			process_squote_state(&lex);
		else if (lex.state == STATE_IN_DQUOTE)
			process_dquote_state(&lex);
	}

	// Ajouter le dernier token s'il y en a un
	add_current_token(&lex);

	// Vérifier si tous les guillemets sont fermés
	if (lex.state != STATE_NORMAL)
	{
		add_token(&lex.tokens, create_token("unclosed quote", TOKEN_ERROR));
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
	}

	free(lex.current_token);
	return (lex.tokens);
}