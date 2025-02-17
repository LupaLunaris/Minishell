#include "minishell.h"
 
 /**
  * Fonction pour afficher les erreurs avec `write`.
  * @param cmd : La commande ou contexte où l'erreur s'est produite (peut être `NULL`).
  * @param message : Le message d'erreur à afficher.
  * @param should_exit : Indique si le programme doit quitter après l'erreur.
  */
 void	error_handler(const char *cmd, const char *message, int should_exit)
 {
	 if (cmd) {
		 // Écrire "minishell: "
		 write(STDERR_FILENO, "minishell: ", 11);
 
		 // Écrire la commande incriminée
		 write(STDERR_FILENO, cmd, strlen(cmd));
 
		 // Ajouter ": "
		 write(STDERR_FILENO, ": ", 2);
	 } else {
		 // Écrire simplement "minishell: " si pas de commande spécifiée
		 write(STDERR_FILENO, "minishell: ", 11);
	 }
 
	 // Écrire le message d'erreur
	 write(STDERR_FILENO, message, strlen(message));
 
	 // Ajouter une nouvelle ligne à la fin
	 write(STDERR_FILENO, "\n", 1);
 
	 // Si should_exit est vrai, quitter le programme
	 if (should_exit)
		 exit(EXIT_FAILURE);
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
