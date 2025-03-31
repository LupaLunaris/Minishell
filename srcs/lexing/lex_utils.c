#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int	is_closed(char *str, char quote)
{
	int	count = 0;
	int	i = 0;

	while(str[i])
	{
		if(str[i] == '\\' && str[i + 1] == '"')
			i += 2;
		if (str[i] == quote)
			count++;
		i++;
	}
	printf("count %d\n", count);
	if (count % 2 != 0 && count > 0)
		return (0);
	if (count == 0)
		return (-1);
	return (1);
}

// int is_closed_by(char *str, char quote)
// {
// 	int closed;
// 	closed = 0;

// 	closed = is_closed(str, quote);

// 	if (is_closed(str,'"') > 0)
// 		return (2);
// 	return (0);
// }

char find_quote(char *prompt,  int *indice)
{
	int i = 0;
	while(prompt[i])
	{

		if (prompt[i] == '"' || prompt[i] == '\'')
		{
			if(prompt[i] == '\\' && prompt[i + 1] == '"')
				i += 2;
			(*indice) = i;
			return (prompt[i]);
		}
		i++;
	}
	return 0;
}
int closer_quote(char *prompt, char quote)
{
	int i;

	i = 0;

	while(prompt[i])
	{
		if(prompt[i] == '\\' && prompt[i + 1] == '"')
			i += 2;
		if (prompt[i++] == quote)
			break ;
		i++;
	}
	i++;
	return (++i);
}

char *handle_double(char *prompt, int last_quote)
{
	char *output;
	int i = 0;
	int j = 0;
	printf("prompt =  %s \n" ,prompt);
	printf("last_quote =  %d \n" ,last_quote);
	output = malloc(strlen(prompt) * 3 + 1);
	while (i < last_quote - 1)// Copie le contenu entre quotes mais sans les quotes elles-mêmes
	{
		if (prompt[i] == '\\') // Dans les guillemets doubles, gère les caractères échappés
		{
			if (prompt[i + 1] == '"' || prompt[i + 1] == '\\' ||
				prompt[i + 1] == '$' || prompt[i + 1] == '\'')
			{
				i++; // Saute le backslash
				output[j++] = prompt[i++]; // Ajoute le caractère échappé
			}
			else
			{
				output[j++] = prompt[i++];// Si ce n'est pas un caractère spécial, garde le backslash
				if (prompt[i])
					output[j++] = prompt[i++];
			}
		}
		else
			output[j++] = prompt[i++];
	}
	output[j] = 0;
	return output;
}


// char *handle_no_quote(char *prompt, int last_quote)
// {
// 	char *output;
// 	int i = 0;
// 	int j = 0;
// 	printf("prompt =  %s \n" ,prompt);
// 	printf("last_quote =  %d \n" ,last_quote);
// 	output = malloc(strlen(prompt) * 3 + 1);
// 	while (i < last_quote - 1)// Copie le contenu entre quotes mais sans les quotes elles-mêmes
// 	{
// 		if (prompt[i] == '\\') // Dans les guillemets doubles, gère les caractères échappés
// 		{
// 			if (prompt[i + 1] == '"' || prompt[i + 1] == '\\' ||
// 				prompt[i + 1] == '$' || prompt[i + 1] == '\'')
// 			{
// 				i++; // Saute le backslash
// 				output[j++] = prompt[i++]; // Ajoute le caractère échappé
// 			}
// 			else
// 			{
// 				output[j++] = prompt[i++];// Si ce n'est pas un caractère spécial, garde le backslash
// 				if (prompt[i])
// 					output[j++] = prompt[i++];
// 			}
// 		}
// 		else
// 			output[j++] = prompt[i++];
// 	}
// 	output[j] = 0;
// 	return output;
// }


// char *handle_quotes(char *prompt, char first_quote, int last_quote)
// {
// 	char *temps;

// 	temps = malloc(strlen(prompt) * 3 + 1);

// 	if (first_quote = '"')
// 		temps = handle_double(&prompt[indice], first_quote, last_quote);
// 	if (first_quote = '\'')
// 		temps = handle_simple(&prompt[indice], first_quote, last_quote);
// 	return (temps);
// }

char *handle_if_quote(char *prompt)
{
	char *temps;
	char first_quote;
	int last_quote;
	int *indice;
	int i = 0;
	int j = 0;

	indice = &i;
	temps = malloc(strlen(prompt) * 3 + 1);
	first_quote = find_quote(prompt, indice); // indice devient l'indice ou se situe la premiere quote
	//printf("indice =  %d \n" ,*indice);
	if (!(is_closed(prompt, first_quote))) // la quote n'est pas fermer
		return(NULL);
	if (is_closed(prompt, '\'') == -1 && is_closed(prompt, '"') == -1) // si il n'y a pas de quote
	{
		printf("il n'y a pas de quote\n");
		return(prompt);
	}
	last_quote = closer_quote(&prompt[(*indice) + 1], first_quote);
	printf("j =  %d \n" ,j);
	printf("indice =  %d \n" ,*indice);
	while( j < *indice)
	{
		printf("indice =  %d \n" ,*indice);
		temps[j++] =  prompt[j++];
	}
	temps[j] = 0;
	//last_quote = closer_quote(&prompt[(*indice)], first_quote); // on recupere l'indice de la quote fermante
	//temps = handle_double(&prompt[*indice + 1], last_quote);  // on gere a partir de la cote "char = first quote" juste l'indice 'last_quote"
	return temps;
}



int main(int ac, char **av)
{
	//char *str = "1234jfs \"'gas \\$ \"\'d";
	(void)ac;
	char *closed;
	closed = handle_if_quote(av[1]);
	printf("is closed : %s\n", closed );
	//printf("is closed ? %s\n", handle_double(str));
}