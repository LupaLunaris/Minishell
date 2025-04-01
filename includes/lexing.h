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

# include "minishell.h"

/* États du lexer */
# define STATE_NORMAL     0
# define STATE_IN_SQUOTE  1
# define STATE_IN_DQUOTE  2

/* Structure d'un token */
typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

/* Structure du lexer */
typedef struct s_lexer
{
	char	*input;         /* Entrée à traiter */
	int		position;       /* Position actuelle dans l'entrée */
	char	*current_token; /* Buffer pour construire le token actuel */
	int		current_pos;    /* Position dans le buffer du token actuel */
	t_token	*tokens;        /* Liste des tokens */
	int		state;          /* État actuel du lexer */
}	t_lexer;

/* Fonctions exportées */
int		is_operator(char c);
int		is_space(char c);
t_token	*lexer(char *input);
t_token	*create_token(char *value, int type);
void	add_token(t_token **tokens, t_token *new_token);
void	free_tokens(t_token *tokens);

#endif