
/*
**** lorsque seul en debut de commande attend la fermeture ****

"\","\"","\\",

*/

#include "minishell.h"
int is_space(char c);
int	error_lexing(char *prompt);
char	*ft_strstr(const char *haystack, const char *needle);

// // Vérifie si l'opérateur de fermeture est présent, start sera defini dans process_opener
// char	*find_matching_closer(char *start, const char *opener)
// {
// 	return ft_strstr(start, opener);
// }

// // Extrait le contenu entre les opérateurs d'ouverture et fermeture
// char	*extract_content(char *opener, char *closer, const char *contenu_str)
// {
// 	char *start;

// 	start = opener + ft_strlen(contenu_str);
// 	*closer = '\0';  // Termine la chaîne au niveau du guillemet fermant
// 	return ft_strdup(start);
// }

// // Recherche un opérateur d'ouverture et son correspondant fermant
// char	*process_opener(char *prompt, const char *contenu_str)
// {
// 	char	*opener;
// 	char	*start;
// 	char	*closer;

// 	opener = ft_strstr(prompt, contenu_str);
// 	if (!opener)
// 		return (NULL);
// 	start = opener + ft_strlen(contenu_str);
// 	closer = find_matching_closer(start, contenu_str);
// 	if (closer)
// 		return extract_content(opener, closer, contenu_str);
// 	return (NULL);  // Opérateur non fermé
// }

// // Fonction principale
// char	*read_no_close(char *prompt, char **opener_ops)
// {
// 	if (!prompt || !opener_ops)
// 		return NULL;

// 	char *copy = ft_strdup(prompt);
// 	if (!copy)
// 		return NULL;

// 	char *result = NULL;
// 	int i = 0;
// 		// Vérifie chaque opérateur d'ouverture
// 	while (opener_ops[i])
// 	{
// 		result = process_opener(copy, opener_ops[i]);
// 		if (result)
// 		{
// 			free(copy);
// 			return result;
// 		}
// 		i++;
// 	}
// 		// Aucun opérateur trouvé, on retourne la chaîne telle quelle
// 	result = ft_strdup(copy);
// 	free(copy);
// 	return result;
// }
// //#include "../../includes/minishell.h"
// char	*lexing(char *prompt)
// {
// 	char *opener_op[3] = {"\'","\"",NULL};
// 	char *read;
// 	char *res;

// 	read = read_no_close(prompt,opener_op);
// 	if (error_lexing(prompt))
// 		return (NULL);
// 	res =  ft_strdup(read);
// 	free(read);
// 	return (res);
// }

// char *opener_op[3] = {"\'","\"",NULL};
// #include "minishell.h"

// // Vérifie si un caractère est un opérateur
// int is_operator(char c)
// {
//	 return (c == '|' || c == '<' || c == '>' || c == ';' || c == '&');
// }

// // Vérifie si un caractère est un espace
// int is_space(char c)
// {
//	 return (c == ' ' || c == '\t' || c == '\n');
// }

// // Fonction pour traiter une séquence entre guillemets
// // Retourne 0 si les guillemets ne sont pas fermés, 1 sinon
// int handle_quotes(char *input, int *i, char *output, int *j, char quote_type)
// {
//	 // Avance après la quote ouvrante
//	 (*i)++;

//	 // Copie le contenu entre quotes mais sans les quotes elles-mêmes
//	 while (input[*i] && input[*i] != quote_type)
//	 {
//		 // Dans les guillemets doubles, gère les caractères échappés
//		 if (quote_type == '"' && input[*i] == '\\' && input[*i + 1])
//		 {
//			 if (input[*i + 1] == '"' || input[*i + 1] == '\\' ||
//				 input[*i + 1] == '$' || input[*i + 1] == '`')
//			 {
//				 (*i)++; // Saute le backslash
//				 output[(*j)++] = input[(*i)++]; // Ajoute le caractère échappé
//			 }
//			 else
//			 {
//				 // Si ce n'est pas un caractère spécial, garde le backslash
//				 output[(*j)++] = input[(*i)++];
//				 if (input[*i])
//					 output[(*j)++] = input[(*i)++];
//			 }
//		 }
//		 else
//		 {
//			 output[(*j)++] = input[(*i)++];
//		 }
//	 }

//	 // Vérifie si la quote a été fermée
//	 if (input[*i] == quote_type)
//	 {
//		 (*i)++; // Avance après la quote fermante
//		 return 1;
//	 }

//	 return 0; // Quote non fermée
// }

// // Fonction pour lexer la ligne de commande
// char *lexing(char *prompt)
// {
//	 char *result;
//	 int i = 0, j = 0;

//	 if (!prompt)
//		 return NULL;

//	 // Alloue de la mémoire pour le résultat
//	 result = malloc(strlen(prompt) * 3 + 1); // Espace supplémentaire pour les espaces ajoutés
//	 if (!result)
//		 return NULL;

//	 while (prompt[i])
//	 {
//		 // Gestion des quotes
//		 if (prompt[i] == '\'' || prompt[i] == '"')
//		 {
//			 char quote_type = prompt[i];

//			 // Si c'est le début d'un mot, pas besoin d'ajouter un espace
//			 if (j > 0 && !is_space(result[j-1]))
//				 result[j++] = ' ';

//			 // Traite le contenu entre quotes
//			 if (!handle_quotes(prompt, &i, result, &j, quote_type))
//			 {
//				 free(result);
//				 printf("bash: syntax error: unclosed quote\n");
//				 return NULL;
//			 }

//			 // Ajoute un espace après si nécessaire
//			 if (prompt[i] && !is_space(prompt[i]) && !is_operator(prompt[i]))
//				 result[j++] = ' ';
//		 }
//		 // Gestion des espaces
//		 else if (is_space(prompt[i]))
//		 {
//			 // Remplace les séquences d'espaces par un seul espace
//			 if (j > 0 && !is_space(result[j-1]))
//				 result[j++] = ' ';
//			 i++;
//		 }
//		 // Gestion des opérateurs
//		 else if (is_operator(prompt[i]))
//		 {
//			 // Ajoute un espace avant si nécessaire
//			 if (j > 0 && !is_space(result[j-1]))
//				 result[j++] = ' ';

//			 // Traitement des opérateurs doubles
//			 if ((prompt[i] == '>' && prompt[i+1] == '>') ||
//				 (prompt[i] == '<' && prompt[i+1] == '<'))
//			 {
//				 result[j++] = prompt[i++];
//				 result[j++] = prompt[i++];
//			 }
//			 else
//			 {
//				 result[j++] = prompt[i++];
//			 }

//			 // Ajoute un espace après si nécessaire
//			 if (prompt[i] && !is_space(prompt[i]))
//				 result[j++] = ' ';
//		 }
//		 // Caractères normaux
//		 else
//		 {
//			 result[j++] = prompt[i++];
//		 }
//	 }

//	 // Termine la chaîne
//	 result[j] = '\0';

//	 // Vérifie les erreurs de syntaxe
//	 if (error_lexing(result))
//	 {
//		 free(result);
//		 return NULL;
//	 }

//	 return result;
// }

// #include "minishell.h"

// // Vérifie les redirections sans cible
// static int check_redirect_errors(char *prompt)
// {
//	 int i = 0;

//	 while (prompt[i])
//	 {
//		 // Cherche les symboles de redirection
//		 if (prompt[i] == '<' || prompt[i] == '>')
//		 {
//			 // Passe au caractère suivant (saut double redirection)
//			 if (prompt[i+1] == prompt[i])
//				 i += 2;
//			 else
//				 i++;

//			 // Saute les espaces
//			 while (prompt[i] && is_space(prompt[i]))
//				 i++;

//			 // Erreur si fin de chaîne ou autre redirection/pipe
//			 if (!prompt[i] || prompt[i] == '<' || prompt[i] == '>' ||
//				 prompt[i] == '|' || prompt[i] == ';')
//			 {
//				 printf("bash: syntax error near unexpected token `newline'\n");
//				 return 1;
//			 }
//		 }
//		 else
//		 {
//			 i++;
//		 }
//	 }

//	 return 0;
// }

// // Vérifie les opérateurs de pipe mal placés
// static int check_pipe_errors(char *prompt)
// {
//	 int i = 0;

//	 // Vérifie si la commande commence par un pipe
//	 while (prompt[i] && is_space(prompt[i]))
//		 i++;

//	 if (prompt[i] == '|')
//	 {
//		 printf("bash: syntax error near unexpected token `|'\n");
//		 return 1;
//	 }

//	 // Vérifie les pipes consécutifs ou pipe en fin de commande
//	 i = 0;
//	 while (prompt[i])
//	 {
//		 if (prompt[i] == '|')
//		 {
//			 i++;
//			 // Saute les espaces
//			 while (prompt[i] && is_space(prompt[i]))
//				 i++;

//			 // Erreur si fin de chaîne ou autre pipe
//			 if (!prompt[i] || prompt[i] == '|')
//			 {
//				 printf("bash: syntax error near unexpected token `|'\n");
//				 return 1;
//			 }
//		 }
//		 else
//		 {
//			 i++;
//		 }
//	 }

//	 return 0;
// }

// // Vérifie le crochet manquant
// static int check_missing_bracket(char *prompt)
// {
//	 int i = 0;
//	 int found_open = 0;
//	 int found_close = 0;

//	 while (prompt[i])
//	 {
//		 if (prompt[i] == '[')
//			 found_open = 1;
//		 else if (prompt[i] == ']')
//			 found_close = 1;
//		 i++;
//	 }

//	 if (found_open && !found_close)
//	 {
//		 printf("bash: [: missing `]'\n");
//		 return 1;
//	 }

//	 return 0;
// }

// // Fonction principale de vérification d'erreurs
// int error_lexing(char *prompt)
// {
//	 if (check_redirect_errors(prompt) ||
//		 check_pipe_errors(prompt) ||
//		 check_missing_bracket(prompt))
//	 {
//		 return 1;
//	 }

//	 return 0;
// }
int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';' || c == '&');
}

// Vérifie si un caractère est un espace
int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

// Fonction pour traiter une séquence entre guillemets
// Retourne 0 si les guillemets ne sont pas fermés, 1 sinon
int handle_quotes(char *input, int *i, char *output, int *j, char quote_type)
{
	// Avance après la quote ouvrante
	(*i)++;

	// Copie le contenu entre quotes mais sans les quotes elles-mêmes
	while (input[*i] && input[*i] != quote_type)
	{
		// Dans les guillemets doubles, gère les caractères échappés
		if (quote_type == '"' && input[*i] == '\\' && input[*i + 1])
		{
			if (input[*i + 1] == '"' || input[*i + 1] == '\\' ||
				input[*i + 1] == '$' || input[*i + 1] == '`')
			{
				(*i)++; // Saute le backslash
				output[(*j)++] = input[(*i)++]; // Ajoute le caractère échappé
			}
			else
			{
				// Si ce n'est pas un caractère spécial, garde le backslash
				output[(*j)++] = input[(*i)++];
				if (input[*i])
					output[(*j)++] = input[(*i)++];
			}
		}
		else
		{
			output[(*j)++] = input[(*i)++];
		}
	}

	// Vérifie si la quote a été fermée
	if (input[*i] == quote_type)
	{
		(*i)++; // Avance après la quote fermante
		return 1;
	}

	return 0; // Quote non fermée
}

// Fonction pour lexer la ligne de commande
char *lexing(char *prompt)
{
	char *result;
	int i = 0, j = 0;

	if (!prompt)
		return NULL;

	// Alloue de la mémoire pour le résultat
	result = malloc(strlen(prompt) * 3 + 1); // Espace supplémentaire pour les espaces ajoutés
	if (!result)
		return NULL;

	while (prompt[i])
	{
		// Gestion des quotes
		if (prompt[i] == '\'' || prompt[i] == '"')
		{
			char quote_type = prompt[i];

			// Si c'est le début d'un mot, pas besoin d'ajouter un espace
			if (j > 0 && !is_space(result[j-1]))
				result[j++] = ' ';

			// Traite le contenu entre quotes
			if (!handle_quotes(prompt, &i, result, &j, quote_type))
			{
				free(result);
				printf("bash: syntax error: unclosed quote\n");
				return NULL;
			}

			// Ajoute un espace après si nécessaire
			if (prompt[i] && !is_space(prompt[i]) && !is_operator(prompt[i]))
				result[j++] = ' ';
		}
		// Gestion des espaces
		else if (is_space(prompt[i]))
		{
			// Remplace les séquences d'espaces par un seul espace
			if (j > 0 && !is_space(result[j-1]))
				result[j++] = ' ';
			i++;
		}
		// Gestion des opérateurs
		else if (is_operator(prompt[i]))
		{
			// Ajoute un espace avant si nécessaire
			if (j > 0 && !is_space(result[j-1]))
				result[j++] = ' ';

			// Traitement des opérateurs doubles
			if ((prompt[i] == '>' && prompt[i+1] == '>') ||
				(prompt[i] == '<' && prompt[i+1] == '<'))
			{
				result[j++] = prompt[i++];
				result[j++] = prompt[i++];
			}
			else
			{
				result[j++] = prompt[i++];
			}

			// Ajoute un espace après si nécessaire
			if (prompt[i] && !is_space(prompt[i]))
				result[j++] = ' ';
		}
		// Caractères normaux
		else
		{
			result[j++] = prompt[i++];
		}
	}

	// Termine la chaîne
	result[j] = '\0';

	// Vérifie les erreurs de syntaxe
	if (error_lexing(result))
	{
		free(result);
		return NULL;
	}

	return result;
}