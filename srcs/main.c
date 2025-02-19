#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_env_list *env_list = init_env(envp);  // Initialise les variables d'environnement en liste chaînée.
    char *rl;
    while (1)
	{ // Boucle infinie pour lancer le prompt.
        rl = readline("MiniShellDeLaMort> "); // Affiche le prompt et récupère l'entrée utilisateur.
        if (!rl) // Quitte si EOF (Ctrl+D).
            break;
        add_history(rl); // Enregistre la commande dans l'historique (readline).
        // PARSING : Analyse l'entrée et convertit en structure(s) t_command.
        t_command *cmds = parse_input(rl, env_list);
        free(rl);
        if (!cmds)
            continue; // Si le parsing échoue, retourne au prompt.
        // BACKEND : Exécute les commandes via le backend.
        execute_command(cmds, envp);
        // Nettoie la mémoire après exécution.
        free_command(cmds);
    }
    printf("exit\n"); 
    return (0);
}
