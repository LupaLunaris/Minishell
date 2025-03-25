
#include "minishell.h"

int is_space(char c);
// Vérifie les redirections sans cible
// static int	check_redirect_errors(char *prompt)
// {
// 	int	i;

// 	i = 0;
// 	while (prompt[i])
// 	{
// 		// Cherche les symboles de redirection
// 		if (prompt[i] == '<' || prompt[i] == '>')
// 		{
// 			if (prompt[i + 1] == prompt[i]) // Passe au caractère suivant (saut double redirection)
// 				i += 2;
// 			else
// 				i++;
// 			while (prompt[i] && is_space(prompt[i])) // Saute les espaces
// 				i++;
// 			if (!prompt[i] || prompt[i] == '<' || prompt[i] == '>' || // Erreur si fin de chaîne ou autre redirection/pipe
// 				prompt[i] == '|' || prompt[i] == ';')
// 			{
// 				printf("bash: syntax error near unexpected token `newline'\n");
// 				return (1);
// 			}
// 		}
// 		else
// 			i++;
// 	}
// 	return (0);
// }

static int	check_in_op(char *op_array, char op)
{
	int	i;

	i = 0;
	while(op_array[i])
	{
		if (op_array[i] == op)
			return (1);
		i++;
	}
	return (0);

}

int	print_error_two(char prompt, char op)
{
	char unexpected_token[] = {'|', '}', ';', '&', '\0'}; // code 2
	char unexpected_token_new[] = {'<','>','\0'};
	char missing_bracket[] = {'[', '\0'}; // code 2
	char usage_filename_arguments[] = {'.', '\0'}; // code 2

	if (check_in_op(unexpected_token, op))
	{
		printf("bash: syntax error near unexpected token `%c'\n",op);
		return (0);
	}
	else if (check_in_op(unexpected_token_new, op))
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (0);
	}
	else if (check_in_op(missing_bracket, op))
		return (printf("bash: missing `]'\n"), 0);
	else if (check_in_op(usage_filename_arguments, op))
	{
		printf("bash: filename argument required\n.: usage: . filename [arguments]\n");
		return (0);
	}
	return (1);
}


int	print_error_other(char prompt, char op)
{
	char Is_a_directory[] = {'/', '\0'};// code: 126
	char home_user_Is_a_directory[] = {'~', '\0'}; // code: 126
	char no_job_control[] = {'%', '\0'}; // code 1

	if (check_in_op(Is_a_directory, op))
	{
		printf("bash: /: Is a directory\n");
		return (0);
	}
	else if (check_in_op(home_user_Is_a_directory, op))
	{
		printf("bash:/home/user Is a directory\n");
		return (0);
	}
	else if (check_in_op(no_job_control, op))
	{
		printf("bash: fg: %%: no such job\n");
		return (0);
	}
	return (1);
}
static int	check_op(char prompt, char op)
{
	if (!print_error_two(prompt, op))
		return (0);
	else if (!print_error_other(prompt, op))
		return (0);
	return (1);
}

// Vérifie les opérateurs de pipe mal placés
static int	check_op_errors(char *prompt, char op)
{
	int	i;

	i = 0;
	while (prompt[i] && is_space(prompt[i])) // Vérifie si la commande commence par un op
		i++;
	if (!check_op(prompt[i], op))
		return(1);
	i = 0;
	while (prompt[i])// Vérifie les pipes consécutifs ou pipe en fin de commande
	{
		if (prompt[i] == op)
		{
			i++;
			while (prompt[i] && is_space(prompt[i])) // Saute les espaces
				i++;
			if (!prompt[i] || prompt[i] == op) // Erreur si fin de chaîne ou autre pipe
			{
				check_op(prompt[i], op);
				return(1);
			}
		}
		else
			i++;
	}
	return 0;
}

// Vérifie le crochet manquant
static int check_missing_bracket(char *prompt)
{
	int i = 0;
	int found_open = 0;
	int found_close = 0;

	while (prompt[i])
	{
		if (prompt[i] == '[')
			found_open = 1;
		else if (prompt[i] == ']')
			found_close = 1;
		i++;
	}

	if (found_open && !found_close)
	{
		printf("bash: [: missing `]'\n");
		return (1);
	}

	return 0;
}

// Fonction principale de vérification d'erreurs
int error_lexing(char *prompt)
{
	if (check_op_errors(prompt,prompt[0]) ||
		check_missing_bracket(prompt))
		return (1);
	return 0;
}