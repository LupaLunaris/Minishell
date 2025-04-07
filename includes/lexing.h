/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:08:00 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 14:08:00 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

/* États du lexer */
# define STATE_NORMAL     0
# define STATE_IN_SQUOTE  1
# define STATE_IN_DQUOTE  2

/* Types de tokens */
# define TOKEN_WORD      1
# define TOKEN_PIPE      2
# define TOKEN_REDIR_IN  3
# define TOKEN_REDIR_OUT 4
# define TOKEN_APPEND    5
# define TOKEN_HEREDOC   6
# define TOKEN_ERROR     7

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_lexer
{
	char	*input;
	int		position;
	char	*current_token;
	int		current_pos;
	t_token	*tokens;
	int		state;
}	t_lexer;

int		is_operator(char c);
int		is_space(char c);
t_token	*lexer(char *input);
t_token	*create_token(char *value, int type);
void	add_token(t_token **tokens, t_token *new_token);
void	add_current_token(t_lexer *lex);
void	free_tokens(t_token *tokens);
void	handle_redirection(t_lexer *lex);
void	handle_pipe(t_lexer *lex);
char	*remove_quotes(char *str, char quote_type);
void	handle_quote(t_lexer *lex, char quote_type);
void	process_dquote_state(t_lexer *lex);
void	process_squote_state(t_lexer *lex);

#endif