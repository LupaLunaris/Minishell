
#include "minishell.h"

// int	error_lexing(char *prompt);
// char	*ft_strstr(const char *haystack, const char *needle);




// static int	is_operator(char c)
// {
// 	return (c == '|' || c == '<' || c == '>' || c == ';' || c == '&');
// }

// int	is_space(char c)
// {
// 	return (c == ' ' || c == '\t' || c == '\n');
// }


// static int handle_quotes(char *input, int *i, char *output, int *j, char quote_type)
// {

// 	(*i)++;
// 	while (input[*i] && input[*i] != quote_type)// Copie le contenu entre quotes mais sans les quotes elles-mêmes
// 	{
// 		if (quote_type == '"' && input[*i] == '\\' && input[*i + 1]) // Dans les guillemets doubles, gère les caractères échappés
// 		{
// 			if (input[*i + 1] == '"' || input[*i + 1] == '\\' ||
// 				input[*i + 1] == '$' || input[*i + 1] == '`')
// 			{
// 				(*i)++; // Saute le backslash
// 				output[(*j)++] = input[(*i)++]; // Ajoute le caractère échappé
// 			}
// 			else
// 			{
// 				output[(*j)++] = input[(*i)++];// Si ce n'est pas un caractère spécial, garde le backslash
// 				if (input[*i])
// 					output[(*j)++] = input[(*i)++];
// 			}
// 		}
// 		else
// 		{
// 			output[(*j)++] = input[(*i)++];
// 		}
// 	}
// 	if (input[*i] == quote_type)// Vérifie si la quote a été fermée
// 	{
// 		(*i)++; // Avance après la quote fermante
// 		return 1;
// 	}
// 	return 0; // Quote non fermée
// }


// // Fonction pour lexer la ligne de commande
// char *lexing(char *prompt)
// {
// 	char *result;
// 	int i = 0, j = 0;

// 	if (!prompt)
// 		return NULL;

// 	// Alloue de la mémoire pour le résultat
// 	result = malloc(strlen(prompt) * 3 + 1); // Espace supplémentaire pour les espaces ajoutés
// 	if (!result)
// 		return NULL;

// 	while (prompt[i])
// 	{
// 		// Gestion des quotes
// 		if (prompt[i] == '\'' || prompt[i] == '"') //prompt[i] == '\'' ||
// 		{
// 			char quote_type = prompt[i];

// 			// Si c'est le début d'un mot, pas besoin d'ajouter un espace
// 			if (j > 0 && !is_space(result[j-1]))
// 				result[j++] = ' ';

// 			// Traite le contenu entre quotes
// 			if (!handle_quotes(prompt, &i, result, &j, quote_type))
// 			{
// 				free(result);
// 				printf("bash: syntax error: unclosed quote\n");
// 				return NULL;
// 			}

// 			// Ajoute un espace après si nécessaire
// 			if (prompt[i] && !is_space(prompt[i]) && !is_operator(prompt[i]))
// 				result[j++] = ' ';
// 		}
// 		// Gestion des espaces
// 		else if (is_space(prompt[i]))
// 		{
// 			// Remplace les séquences d'espaces par un seul espace
// 			if (j > 0 && !is_space(result[j-1]))
// 				result[j++] = ' ';
// 			i++;
// 		}
// 		// Gestion des opérateurs
// 		else if (is_operator(prompt[i]))
// 		{
// 			// Ajoute un espace avant si nécessaire
// 			if (j > 0 && !is_space(result[j-1]))
// 				result[j++] = ' ';

// 			// Traitement des opérateurs doubles
// 			if ((prompt[i] == '>' && prompt[i+1] == '>') ||
// 				(prompt[i] == '<' && prompt[i+1] == '<'))
// 			{
// 				result[j++] = prompt[i++];
// 				result[j++] = prompt[i++];
// 			}
// 			else
// 			{
// 				result[j++] = prompt[i++];
// 			}

// 			// Ajoute un espace après si nécessaire
// 			if (prompt[i] && !is_space(prompt[i]))
// 				result[j++] = ' ';
// 		}
// 		// Caractères normaux
// 		else
// 		{
// 			result[j++] = prompt[i++];
// 		}
// 	}

// 	// Termine la chaîne
// 	result[j] = '\0';

// 	// Vérifie les erreurs de syntaxe
// 	if (error_lexing(result))
// 	{
// 		free(result);
// 		return "NULL";
// 	}

// 	return result;
// }

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   lexer.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: student <student@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/30 10:00:00 by student           #+#    #+#             */
// /*   Updated: 2025/03/30 10:00:00 by student          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// static int	is_operator(char c)
// {
// 	if (c == '|')
// 		return (1);
// 	if (c == '<')
// 		return (1);
// 	if (c == '>')
// 		return (1);
// 	if (c == ';')
// 		return (1);
// 	if (c == '&')
// 		return (1);
// 	return (0);
// }

// int	is_space(char c)
// {
// 	if (c == ' ')
// 		return (1);
// 	if (c == '\t')
// 		return (1);
// 	if (c == '\n')
// 		return (1);
// 	return (0);
// }

// /* Processes characters after a backslash in double quotes */
// static int	handle_escape(char *input, int *i, char *output, int *j)
// {
// 	(*i)++;
// 	if (input[*i] == '"' || input[*i] == '\\' ||
// 		input[*i] == '$' || input[*i] == '`')
// 	{
// 		output[(*j)++] = input[(*i)++];
// 		return (1);
// 	}
// 	output[(*j)++] = '\\';
// 	if (input[*i])
// 		output[(*j)++] = input[(*i)++];
// 	return (1);
// }

// /* Processes content between quotes */
// static int	handle_quotes_content(char *input, int *i, char *output, int *j)
// {
// 	char	quote_type;

// 	quote_type = input[*i];
// 	(*i)++;
// 	while (input[*i] && input[*i] != quote_type)
// 	{
// 		if (quote_type == '"' && input[*i] == '\\' && input[*i + 1])
// 			handle_escape(input, i, output, j);
// 		else
// 			output[(*j)++] = input[(*i)++];
// 	}
// 	if (input[*i] == quote_type)
// 	{
// 		(*i)++;
// 		return (1);
// 	}
// 	return (0);
// }

// /* Handles quotes and surrounding spaces */
// static int	handle_quotes(char *input, int *i, char *output, int *j)
// {
// 	if ((*j) > 0 && !is_space(output[(*j) - 1]))
// 		output[(*j)++] = ' ';
// 	if (!handle_quotes_content(input, i, output, j))
// 	{
// 		printf("bash: syntax error: unclosed quote\n");
// 		return (0);
// 	}
// 	if (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]))
// 		output[(*j)++] = ' ';
// 	return (1);
// }

// /* Processes spaces in input */
// static int	handle_spaces(int *i, char *output, int *j)
// {
// 	if ((*j) > 0 && !is_space(output[(*j) - 1]))
// 		output[(*j)++] = ' ';
// 	(*i)++;
// 	return (1);
// }

// /* Handles double operators like >> and << */
// static int	handle_double_op(char *input, int *i, char *output, int *j)
// {
// 	output[(*j)++] = input[(*i)++];
// 	output[(*j)++] = input[(*i)++];
// 	return (1);
// }

// /* Processes operators in input */
// static int	handle_operators(char *input, int *i, char *output, int *j)
// {
// 	if ((*j) > 0 && !is_space(output[(*j) - 1]))
// 		output[(*j)++] = ' ';

// 	if ((input[*i] == '>' && input[*i + 1] == '>') ||
// 		(input[*i] == '<' && input[*i + 1] == '<'))
// 		handle_double_op(input, i, output, j);
// 	else
// 		output[(*j)++] = input[(*i)++];

// 	if (input[*i] && !is_space(input[*i]))
// 		output[(*j)++] = ' ';
// 	return (1);
// }

// /* Processes regular characters */
// static int	handle_regular_char(char *input, int *i, char *output, int *j)
// {
// 	output[(*j)++] = input[(*i)++];
// 	return (1);
// }

// /* Main processing function */
// static int	process_input(char *input, char *result)
// {
// 	int	i;
// 	int	j;
// 	int	success;

// 	i = 0;
// 	j = 0;
// 	success = 1;
// 	while (input[i] && success)
// 	{
// 		if (input[i] == '\'' || input[i] == '"')
// 			success = handle_quotes(input, &i, result, &j);
// 		else if (is_space(input[i]))
// 			handle_spaces(&i, result, &j);
// 		else if (is_operator(input[i]))
// 			handle_operators(input, &i, result, &j);
// 		else
// 			handle_regular_char(input, &i, result, &j);
// 	}
// 	result[j] = '\0';
// 	return (success);
// }

// /* Main lexing function */
// char	*lexing(char *prompt)
// {
// 	char	*result;
// 	int		success;

// 	if (!prompt)
// 		return (NULL);
// 	result = malloc(strlen(prompt) * 3 + 1);
// 	if (!result)
// 		return (NULL);
// 	success = process_input(prompt, result);
// 	if (!success)
// 	{
// 		free(result);
// 		return (NULL);
// 	}
// 	return (result);
// }
static int	is_operator(char c)
{
	if (c == '|')
		return (1);
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	if (c == ';')
		return (1);
	if (c == '&')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	return (0);
}

/* Processes characters after a backslash in double quotes */
static int	handle_dquote_escape(char *input, int *i, char *output, int *j)
{
	(*i)++; // Skip the backslash
	if (input[*i] == '"' || input[*i] == '\\' ||
		input[*i] == '$' || input[*i] == '`')
	{
		output[(*j)++] = input[(*i)++]; // Copy the escaped character only
	}
	else
	{
		output[(*j)++] = '\\'; // Keep the backslash
		if (input[*i])
			output[(*j)++] = input[(*i)++]; // Copy the next character
	}
	return (1);
}

/* Add single quotes around a word in a single-quoted string */
static void	add_squote_word(char *output, int *j, char *word_buf, int *w_idx)
{
	int	k;

	if (*w_idx > 0)
	{
		output[(*j)++] = '\''; // Opening quote
		k = 0;
		while (k < *w_idx)
			output[(*j)++] = word_buf[k++];
		output[(*j)++] = '\''; // Closing quote

		*w_idx = 0; // Reset word buffer
	}
}

/* Handles content of single quotes - splits into separately quoted words */
static int	handle_squote_content(char *input, int *i, char *output, int *j)
{
	char	word_buf[1024]; // Buffer for current word
	int		w_idx;

	(*i)++; // Skip opening quote
	w_idx = 0;
	while (input[*i] && input[*i] != '\'')
	{
		if (is_space(input[*i]))
		{
			add_squote_word(output, j, word_buf, &w_idx);
			output[(*j)++] = ' ';
			(*i)++;
		}
		else
		{
			word_buf[w_idx++] = input[(*i)++];
		}
	}
	add_squote_word(output, j, word_buf, &w_idx);

	if (input[*i] == '\'')
	{
		(*i)++; // Skip closing quote
		return (1);
	}
	return (0); // Unclosed quote
}

/* Handles content of double quotes - preserves as is */
static int	handle_dquote_content(char *input, int *i, char *output, int *j)
{
	(*i)++; // Skip opening quote
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '\\' && input[*i + 1])
			handle_dquote_escape(input, i, output, j);
		else
			output[(*j)++] = input[(*i)++];
	}

	if (input[*i] == '"')
	{
		(*i)++; // Skip closing quote
		return (1);
	}
	return (0); // Unclosed quote
}

/* Handles quotes and surrounding spaces */
static int	handle_quotes(char *input, int *i, char *output, int *j)
{
	int	success;

	if ((*j) > 0 && !is_space(output[(*j) - 1]))
		output[(*j)++] = ' ';

	if (input[*i] == '\'')
		success = handle_squote_content(input, i, output, j);
	else
	{
		// For double quotes, just process the content without adding quotes
		success = handle_dquote_content(input, i, output, j);
	}

	if (!success)
	{
		printf("bash: syntax error: unclosed quote\n");
		return (0);
	}

	if (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]))
		output[(*j)++] = ' ';

	return (1);
}

/* Processes spaces in input */
static int	handle_spaces(int *i, char *output, int *j)
{
	if ((*j) > 0 && !is_space(output[(*j) - 1]))
		output[(*j)++] = ' ';
	(*i)++;
	return (1);
}

/* Handles double operators like >> and << */
static int	handle_double_op(char *input, int *i, char *output, int *j)
{
	output[(*j)++] = input[(*i)++];
	output[(*j)++] = input[(*i)++];
	return (1);
}

/* Processes operators in input */
static int	handle_operators(char *input, int *i, char *output, int *j)
{
	if ((*j) > 0 && !is_space(output[(*j) - 1] ))
		output[(*j)++] = ' ';

	if ((input[*i] == '>' && input[*i + 1] == '>') ||
		(input[*i] == '<' && input[*i + 1] == '<'))
		handle_double_op(input, i, output, j);
	else
		output[(*j)++] = input[(*i)++];

	if (input[*i] && !is_space(input[*i]))
		output[(*j)++] = ' ';

	return (1);
}
/* Processes regular characters */
static int	handle_regular_char(char *input, int *i, char *output, int *j)
{
	output[(*j)++] = input[(*i)++];
	return (1);
}

/* Main processing function */
static int	process_input(char *input, char *result)
{
	int	i;
	int	j;
	int	success;

	i = 0;
	j = 0;
	success = 1;
	while (input[i] && success)
	{
		if (input[i] == '\'' || input[i] == '"')
			success = handle_quotes(input, &i, result, &j);
		else if (is_space(input[i]))
			handle_spaces(&i, result, &j);
		else if (is_operator(input[i]))
			handle_operators(input, &i, result, &j);
		else
			handle_regular_char(input, &i, result, &j);
	}
	result[j] = '\0';
	return (success);
}

/* Main lexing function */
char	*lexing(char *prompt)
{
	char	*result;
	int		success;

	if (!prompt)
		return (NULL);
	result = malloc(strlen(prompt) * 3 + 1);
	if (!result)
		return (NULL);
	success = process_input(prompt, result);
	if (!success)
	{
		free(result);
		return (NULL);
	}
	return (result);
}