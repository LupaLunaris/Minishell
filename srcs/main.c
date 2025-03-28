/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:17:31 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/28 10:47:19 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_signals_and_input(t_shell_data *data, char **rl, int *final_status)
{
    // Lire l'entrée utilisateur avec readline
    *rl = readline("MiniShellDeLaMort> ");
    
    if (*rl == NULL) // L'utilisateur a entré EOF (Ctrl+D)
    {
        if (data->interactive)
            write(STDOUT_FILENO, "exit\n", 5);
        *final_status = data->exit_status;
        return;
    }

    if ((*rl)[0] != '\0') // Ajoute à l'historique uniquement si non vide
        add_history(*rl);

    // Passer aux signaux "non-interactifs" pour la suite
    set_signals_noninteractive();
}


void execute_user_command(t_shell_data *data, const char *rl, char **envp)
{
    char **splited_args;
    t_cmd *cmds;

    // Splitte la commande en arguments (selon les espaces)
    splited_args = ft_split(rl, ' ');
    if (!splited_args)
        return;

    // Analyse syntaxique de la commande
    cmds = parser(splited_args);
    if (!cmds)
    {
        free_split(splited_args);
        return;
    }

    // Expansion des variables d'environnement dans la commande
    var_expend(data->env_list, cmds);

    // Ajouter les fonctions internes (builtins) au shell
    add_builtin(cmds);

    // Exécuter les commandes
    data->exit_status = execute(cmds, data->env_list, data);

    // Libérer les structures associées
    free_command(cmds);
    free_split(splited_args);

    // Gérer les signaux reçus (SIGINT, SIGQUIT)
    if (g_signal_received == SIGINT)
        data->exit_status = 130; // 128 + SIGINT
    else if (g_signal_received == SIGQUIT)
        data->exit_status = 131; // 128 + SIGQUIT
}

int main(int argc, char **argv, char **envp)
{
    t_shell_data *data;
    int final_status = 0;
    char *rl = NULL; // Déclaration explicite de rl

    // Vérification des arguments
    if (argc != 1 || !argv)
        return 1;

    // Initialiser les données du shell
    data = initialize_shell_data(envp);
    if (!data)
        return 1;

    // Boucle principale
    while (1)
    {
        // Réinitialisation des signaux et test interactif
        g_signal_received = 0;
        if (data->interactive)
            set_signals_interactive();

        // Gestion des signaux et de l'input utilisateur
        handle_signals_and_input(data, &rl, &final_status);
        if (final_status) // Si final_status != 0, sortir de la boucle
            break;

        // Si une commande a été récupérée, l'exécuter
        if (rl)
        {
            execute_user_command(data, rl, envp);
            free(rl); // Libérer rl après exécution
            rl = NULL; // Prévenir les doublons de libération
        }
    }

    // Nettoyer les ressources restantes
    cleanup_resources(data);

    return (final_status); // Retourner le code de sortie final
}
