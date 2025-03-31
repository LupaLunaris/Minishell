/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:17:31 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 18:34:09 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_shell_data *init_shell_data(char **envp)
{
    t_shell_data *data = malloc(sizeof(t_shell_data));
    if (!data)
        return NULL;
    data->exit_status = 0;
    data->interactive = isatty(STDIN_FILENO);
    data->env_list = init_env(envp);
    return data;
}

void handle_signals_and_input(t_shell_data *data, char **rl, int *should_exit)
{
    *rl = readline("MiniShellDeLaMort> ");
    
    if (*rl == NULL)
    {
        if (data->interactive)
            write(STDOUT_FILENO, "exit\n", 5);
        *should_exit = 1;
        return;
    }

    if ((*rl)[0] != '\0')
        add_history(*rl);

    set_signals_noninteractive();
}

int process_command(char *input, t_shell_data *data)
{
    char *lexed_input;
    char **tokens;
    t_cmd *cmd_list;
    int ret;
    
    // Étape 1: Lexer la ligne d'entrée
    lexed_input = lexing(input);
    if (!lexed_input)
        return 1; // Une erreur est déjà affichée dans lexing
    
    // Étape 2: Séparer en tokens
    tokens = ft_split(lexed_input, ' ');
    free(lexed_input);
    if (!tokens)
        return (error_handler("memory allocation", NULL, 0, EXIT_FAILURE));
    
    // Étape 3: Parser les tokens en structure de commande
    cmd_list = parser(tokens);
    
    // Libérer les tokens
    free_arr(tokens);
    
    if (!cmd_list)
        return (error_handler("parsing", NULL, 0, EXIT_FAILURE));
    
    // Étape 4: Identifier les builtins
    add_builtin(cmd_list);
    
    // Étape 5: Exécuter les commandes
    ret = execute(cmd_list, data->env_list, data);
    
    // Étape 6: Nettoyer
    clean_cmd_list(cmd_list);
    
    return ret;
}

int main(int argc, char **argv, char **envp)
{
    char *rl = NULL;
    char *lexed = NULL;
    char **tokens = NULL;
    t_cmd *cmds = NULL;
    t_shell_data *data = NULL;

    // Vérifier les arguments
    if (argc != 1 || !argv)
        return 1;

    // Initialiser la structure t_shell_data
    data = malloc(sizeof(t_shell_data));
    if (!data)
        cleanup_and_exit("malloc", "Échec d'allocation mémoire", NULL, NULL, EXIT_FAILURE);

    // Initialisation des données du shell
    data->exit_status = 0;
    data->interactive = isatty(STDIN_FILENO);
    data->env_list = init_env(envp);
    if (!data->env_list)
        cleanup_and_exit("init_env", "Échec d'initialisation des variables d'environnement", data, NULL, EXIT_FAILURE);

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
            break;  // Sortie immédiate de la boucle
        }

        // Ajouter à l'historique si non vide
        if (rl[0] != '\0')
            add_history(rl);

        // Lexing
        lexed = lexing(rl);
        if (!lexed)
        {
            free(rl);
            continue;
        }

        // Passer en mode non-interactif avant d'exécuter la commande
        set_signals_noninteractive();

        // Parsing et préparation des commandes
        tokens = ft_split(lexed, ' ');
        free(lexed);
        
        if (!tokens)
        {
            free(rl);
            error_handler("memory allocation", NULL, 0, EXIT_FAILURE);
            continue;
        }

        cmds = parser(tokens);
        free_arr(tokens);
        
        if (cmds)
        {
            // Expansion des variables
            var_expend(data->env_list, cmds, data);
            
            // Ajout des builtins
            add_builtin(cmds);
            
            // Exécution des commandes
            data->exit_status = execute(cmds, data->env_list, data);
            
            // Nettoyage des commandes
            free_command(cmds);
            cmds = NULL;
        }

        // Vérifier si un signal a été reçu pendant l'exécution
        if (g_signal_received == SIGINT)
            data->exit_status = 130;  // 128 + SIGINT (2)
        else if (g_signal_received == SIGQUIT)
            data->exit_status = 131;  // 128 + SIGQUIT (3)

        // Libérer rl pour la prochaine itération
        free(rl);
        rl = NULL;
    }

    // Nettoyer et quitter proprement
    cleanup_and_exit(NULL, NULL, data, NULL, data->exit_status);
    
    // Cette ligne ne sera jamais atteinte
    return data->exit_status;
}
