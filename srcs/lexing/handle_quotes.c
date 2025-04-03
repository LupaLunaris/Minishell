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
/*
** Fonction pour supprimer les guillemets des tokens tout en préservant
** les guillemets imbriqués.
*/
// Fonction pour supprimer les guillemets d'une chaîne
// en préservant les guillemets imbriqués
// Fonction pour supprimer uniquement les guillemets externes d'une chaîne
char	*remove_quotes(char *str, char quote_type)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	if (!str)
		return (NULL);
	len = strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	if (len > 0 && (str[0] == '"' || str[0] == '\''))
		quote_type = str[0];
	i = 0;
	j = 0;
	if (quote_type != 0)
		i++;
	while (i < len)
	{
		if (quote_type != 0 && str[i] == quote_type && i == len - 1)
			break ;
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

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
