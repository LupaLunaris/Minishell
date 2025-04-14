/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:06:26 by malafont          #+#    #+#             */
/*   Updated: 2025/04/03 12:06:36 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote(t_lexer *lex, char quote_type)
{
	lex->current_token[lex->current_pos++] = quote_type;
	lex->position++;
	if (quote_type == '\'')
		lex->state = STATE_IN_SQUOTE;
	else if (quote_type == '"')
		lex->state = STATE_IN_DQUOTE;
}

/* Gère l'état dans des guillemets simples */
void	process_squote_state(t_lexer *lex)
{
	char	c;

	c = lex->input[lex->position];
	lex->current_token[lex->current_pos++] = c;
	lex->position++;
	if (c == '\'')
		lex->state = STATE_NORMAL;
}

/* Gère l'état dans des guillemets doubles */
void	process_dquote_state(t_lexer *lex)
{
	char	c;

	c = lex->input[lex->position];
	lex->current_token[lex->current_pos++] = c;
	lex->position++;
	if (c == '"')
		lex->state = STATE_NORMAL;
}
