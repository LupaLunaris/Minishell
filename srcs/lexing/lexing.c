/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:13:08 by malafont          #+#    #+#             */
/*   Updated: 2025/04/03 12:13:15 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* Gère un caractère normal (ni espace, ni opérateur, ni guillemet) */
static void	handle_normal_char(t_lexer *lex)
{
	lex->current_token[lex->current_pos++] = lex->input[lex->position];
	lex->position++;
}

/* Gère l'état normal (hors guillemets) */
static void	process_normal_state(t_lexer *lex)
{
	char	c;

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
	add_current_token(&lex);
	if (lex.state != STATE_NORMAL)
	{
		add_token(&lex.tokens, create_token("unclosed quote", TOKEN_ERROR));
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
	}
	free(lex.current_token);
	return (lex.tokens);
}
