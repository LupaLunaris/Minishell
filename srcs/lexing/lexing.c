
#include "minishell.h"

static int is_operator(char c)
{
    if (c == '|' || c == '<' || c == '>' || c == ';' || c == '&')
        return (1);
    return (0);
}

int is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n')
        return (1);
    return (0);
}

/* Processes characters after a backslash in double quotes */
static int handle_dquote_escape(char *input, int *i, char *output, int *j)
{
    if (!input[*i])
        return (0);
    
    (*i)++; // Skip the backslash
    if (!input[*i])
        return (0);
        
    if (input[*i] == '"' || input[*i] == '\\' || input[*i] == '$' || input[*i] == '`')
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

/* Handles content of single quotes - preserves literal content */
static int handle_squote_content(char *input, int *i, char *output, int *j)
{
    (*i)++; // Skip opening quote
    
    // Copy content literally
    while (input[*i] && input[*i] != '\'')
    {
        output[(*j)++] = input[(*i)++];
    }
    
    if (input[*i] == '\'')
    {
        (*i)++; // Skip closing quote
        return (1);
    }
    return (0); // Unclosed quote
}

/* Handles content of double quotes - preserves as is */
static int handle_dquote_content(char *input, int *i, char *output, int *j)
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

/* Handles quotes without adding unnecessary spaces */
static int handle_quotes(char *input, int *i, char *output, int *j)
{
    int success;
    
    // Traiter le contenu des guillemets
    if (input[*i] == '\'')
        success = handle_squote_content(input, i, output, j);
    else
        success = handle_dquote_content(input, i, output, j);
    
    if (!success)
    {
        printf("bash: syntax error: unclosed quote\n");
        return (0);
    }
    
    return (1);
}

/* Processes spaces in input */
static int handle_spaces(int *i, char *output, int *j)
{
    if ((*j) > 0 && !is_space(output[(*j) - 1]))
        output[(*j)++] = ' ';
    (*i)++;
    return (1);
}

/* Handles double operators like >> and << */
static int handle_double_op(char *input, int *i, char *output, int *j)
{
    output[(*j)++] = input[(*i)++];
    if (input[*i]) // Vérification de sécurité
        output[(*j)++] = input[(*i)++];
    return (1);
}

/* Processes operators in input */
static int handle_operators(char *input, int *i, char *output, int *j)
{
	if (!input[*i])
        return (0);
    // Ajouter un espace avant l'opérateur si nécessaire
    if ((*j) > 0 && !is_space(output[(*j) - 1]))
        output[(*j)++] = ' ';

    // Traiter les opérateurs doubles
    if ((input[*i] == '>' && input[*i + 1] == '>') ||
        (input[*i] == '<' && input[*i + 1] == '<'))
        handle_double_op(input, i, output, j);
    else
        output[(*j)++] = input[(*i)++];

    // Ajouter un espace après l'opérateur si nécessaire et si ce n'est pas un espace
    if (input[*i] && !is_space(input[*i]))
        output[(*j)++] = ' ';

    return (1);
}

/* Processes regular characters */
static int handle_regular_char(char *input, int *i, char *output, int *j)
{
    if (!input[*i])
        return (0);
        
    output[(*j)++] = input[(*i)++];
    return (1);
}

/* Main processing function */
static int process_input(char *input, char *result)
{
    int i = 0;
    int j = 0;
    int success = 1;
    
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
char *lexing(char *prompt)
{
    char *result;
    int success;

    if (!prompt)
        return (NULL);
    
    // Allouer suffisamment d'espace pour le pire scénario
    result = malloc(strlen(prompt) * 3 + 1);
    if (!result)
        return (NULL);
    
    success = process_input(prompt, result);
    if (!success)
    {
        free(result);
        return (NULL);
    }
    
    // Optimisation: réduire la mémoire au minimum nécessaire
    char *trimmed = strdup(result);
    free(result);
    return (trimmed);
}
