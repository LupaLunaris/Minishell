#include "minishell.h"
#include "execute.h"
/*
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
*/
// Test commande echo backend

int main(int argc, char **argv, char **envp)
{
    // Code de démarrage
    (void)argc;
    (void)argv;

    printf("Bienvenue dans Minishell !\n");
    // Commande simulée : echo "hello" > out.txt
    t_command command;
    command.cmd = "echo";                          // Nom commande
    char *args[] = {"echo", "hello", NULL};        // Arguments fournis
    command.args = args;                           // Associe args
    command.input_file = NULL;                     // Pas de redirection d’entrée
    command.output_file = "out.txt";               // Redirection de sortie
    command.append = 0;                            // Pas de mode ">>"
    command.next = NULL;                           // Pas de pipe
/*
	t_command command1;
    command1.cmd = "cat";
    char *args1[] = {"cat", NULL}; 
    command1.args = args1;
    command1.input_file = "input.txt";  // Redirection d’entrée
    command1.output_file = NULL;
    command1.append = 0;
    command1.next = NULL;

    // Commande 2 : grep "hello" > out.txt
    t_command command2;
    command2.cmd = "grep";
    char *args2[] = {"grep", "hello", NULL};
    command2.args = args2;
    command2.input_file = NULL;
    command2.output_file = "out.txt"; // Redirection de sortie
    command2.append = 0; 
    command2.next = NULL;

    // Chaîne les deux commandes avec un pipe
    command1.next = &command2;
*/
    int ret = execute_command(&command, envp);
    if (ret == 0)
        printf("Test passed: echo command executed successfully.\n");
    else
        printf("Test failed: echo command returned error code %d.\n", ret);

    return (0);
}
