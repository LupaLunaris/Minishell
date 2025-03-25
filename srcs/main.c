#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *rl;
    char **splited_args;
    t_cmd *cmds;
    int final_status = 0;

    if (argc != 1 || !argv)
        return 1;
    
    // Initialiser la structure t_shell_data
    t_shell_data *data = malloc(sizeof(t_shell_data));
    if (!data)
        return 1;
    
    // Initialisation des données du shell
    data->exit_status = 0;
    data->interactive = isatty(STDIN_FILENO);
    t_env_list *env_list = init_env(envp);
    
    // Boucle principale du shell
    while (1)
    {
        // Réinitialiser l'état des signaux pour chaque nouvelle commande
        g_signal_received = 0;
        
        // Configurer les signaux en mode interactif avant de demander une entrée utilisateur
        if (data->interactive)
            set_signals_interactive();
        
        // Lire l'entrée de l'utilisateur
        rl = readline("MiniShellDeLaMort> ");
        
        // Traitement explicite de Ctrl+D (EOF)
        if (rl == NULL)
        {
            if (data->interactive)
                write(STDOUT_FILENO, "exit\n", 5);
            final_status = data->exit_status;
            break;  // Sortie immédiate de la boucle
        }
        
        // Traiter la ligne saisie si elle n'est pas vide
        if (rl[0] != '\0')
        {
            add_history(rl);
            
            // Passer en mode non-interactif avant d'exécuter la commande
            if (data->interactive)
                set_signals_noninteractive();
            
            // Parsing et préparation des commandes
            splited_args = ft_split(rl, ' ');
            cmds = parser(splited_args);
            free(rl);
            
            // Exécution des commandes
            if (cmds)
            {
                add_builtin(cmds);
                data->exit_status = execute(cmds, env_list, data);
                free_command(cmds);
            }
            
            // Vérifier si un signal a été reçu pendant l'exécution
            if (g_signal_received == SIGINT)
                data->exit_status = 130;  // 128 + SIGINT (2)
            else if (g_signal_received == SIGQUIT)
                data->exit_status = 131;  // 128 + SIGQUIT (3)
        }
        else
        {
            free(rl);
        }
    }
    
    // Libérer les ressources
    if (env_list)
        free_env_list(env_list);
    
    // Libérer la mémoire allouée pour data
    free(data);
    rl_clear_history();
    
    return (final_status);
}
