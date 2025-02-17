#include "minishell.h"

void	cleanup_and_exit(const char *message, int exit_code)
{
    // Libère les ressources ici
    
    // Appelle l'error_handler pour afficher un message d'erreur, puis quitte
    error_handler(NULL, message, 1);
    exit(exit_code);
}
