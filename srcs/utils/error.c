#include "minishell.h"
 
 /**
  * Fonction pour afficher les erreurs avec `write`.
  * @param cmd : La commande ou contexte où l'erreur s'est produite (peut être `NULL`).
  * @param message : Le message d'erreur à afficher.
  * @param should_exit : Indique si le programme doit quitter après l'erreur.
  */
int	error_handler(const char *cmd, const char *message, int should_exit, int error_code)
{
	if (message && strlen(message) > 0)
	{ // Afficher uniquement si un message est fourni
		if (cmd)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, cmd, strlen(cmd));
			write(STDERR_FILENO, ": ", 2);
		}
		else
			write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, message, strlen(message));
		write(STDERR_FILENO, "\n", 1);
	}
	if (should_exit)
		exit(error_code);
	return error_code;
}
 
 void	warning_handler(const char *cmd, const char *message)
{
	if (cmd)
	{
		write(STDERR_FILENO, "minishell: warning: ", 20);
		write(STDERR_FILENO, cmd, strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	else
		write(STDERR_FILENO, "minishell: warning: ", 20);
	write(STDERR_FILENO, message, strlen(message));
	write(STDERR_FILENO, "\n", 1);
}
