#include "minishell.h"

// typedef struct s_lex_error
// {
// 	char	*op_array;
// 	char	*msg;
// 	int		erno;

// }  t_lex_error;

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
		printf("bash: /: %c Is a directory\n",op);
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




