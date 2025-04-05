/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pipe_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:09:32 by malafont          #+#    #+#             */
/*   Updated: 2025/04/03 12:11:49 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* Finalise le token courant et l'ajoute à la liste */
void	add_current_token(t_lexer *lex)
{
	if (lex->current_pos > 0)
	{
		lex->current_token[lex->current_pos] = '\0';
		add_token(&lex->tokens, create_token(lex->current_token, TOKEN_WORD));
		lex->current_pos = 0;
	}
}

/* Gère une redirection de type input (<, <<) */
static void	handle_input_redirection(t_lexer *lex)
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
static void	handle_output_redirection(t_lexer *lex)
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
void	handle_redirection(t_lexer *lex)
{
	add_current_token(lex);
	if (lex->input[lex->position] == '<')
		handle_input_redirection(lex);
	else if (lex->input[lex->position] == '>')
		handle_output_redirection(lex);
}

/* Gère un pipe */
void	handle_pipe(t_lexer *lex)
{
	add_current_token(lex);
	add_token(&lex->tokens, create_token("|", TOKEN_PIPE));
	lex->position++;
}
