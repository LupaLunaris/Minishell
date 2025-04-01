/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:17:31 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/01 10:15:00 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initialise les données du shell */
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

/* Gère les signaux et l'entrée utilisateur */
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

/* Fonction utilitaire pour afficher les informations de commande */
void print_cmd_info(t_cmd *cmd)
{
    int i;
    t_redirection *redir;

    printf("\n=== Commande ===\n");
    printf("cmd: %s\n", cmd->cmd ? cmd->cmd : "(null)");
    printf("args: ");
    if (cmd->args)
    {
        i = 0;
        while (cmd->args[i])
        {
            printf("[%s] ", cmd->args[i]);
            i++;
        }
    }
    printf("\nis_builtin: %d\n", cmd->is_builtin);

    // Afficher les redirections
    redir = cmd->redirections;
    while (redir)
    {
        printf("Redirection: ");
        switch (redir->type)
        {
            case REDIR_INPUT:
                printf("< %s\n", redir->file);
                break;
            case REDIR_OUTPUT:
                printf("> %s\n", redir->file);
                break;
            case REDIR_APPEND:
                printf(">> %s\n", redir->file);
                break;
            case REDIR_HEREDOC:
                printf("<< %s\n", redir->file);
                if (redir->heredoc_content)
                    printf("  Content: %s\n", redir->heredoc_content);
                break;
            default:
                printf("Type inconnu\n");
        }
        redir = redir->next;
    }
}

/* Fonction utilitaire pour afficher toute la liste de commandes */
void print_cmd_list(t_cmd *head)
{
    t_cmd *current = head;
    int cmd_num = 1;

    printf("\n===== Liste des commandes =====\n");
    while (current)
    {
        printf("\nCommande #%d:\n", cmd_num++);
        print_cmd_info(current);

        // Indiquer s'il y a une commande suivante (après un pipe)
        if (current->next)
            printf("\n| (pipe)\n");

        current = current->next;
    }
    printf("\n=============================\n");
}

/* Traite une commande saisie par l'utilisateur */
int process_command(char *input, t_shell_data *data)
{
    t_cmd *cmd_list;
    int ret;

    // Ignorer les entrées vides
    if (!input || input[0] == '\0')
        return (0);

    // Étape 1: Parsing complet (lexing + parsing)
    cmd_list = parse_input(input);
    if (!cmd_list)
        return (1); // Erreur déjà affichée dans parse_input

    // Étape 2: Configuration des heredocs
    t_cmd *curr = cmd_list;
    while (curr)
    {
        t_redirection *redir = curr->redirections;
        while (redir)
        {
            if (redir->type == REDIR_HEREDOC && (!redir->heredoc_content || ft_strlen(redir->heredoc_content) == 0))
            {
                int status = process_heredoc(redir->file, curr);
                if (status != 0)
                {
                    clean_cmd_list(cmd_list);
                    return (status);
                }
            }
            redir = redir->next;
        }
        curr = curr->next;
    }

    // Étape 3: Expansion des variables
    var_expend(data->env_list, cmd_list, data);

    // Cas particulier: les variables vides
    if (cmd_list && cmd_list->cmd && cmd_list->cmd[0] == '$')
    {
        // Si c'est une variable d'environnement vide, on affiche juste rien
        if (!ft_strchr(cmd_list->cmd, '/'))
        {
            clean_cmd_list(cmd_list);
            return (0);
        }
    }

    // Étape 4: Exécution
    ret = execute(cmd_list, data->env_list, data);

    // Étape 5: Nettoyage
    clean_cmd_list(cmd_list);

    return (ret);
}

int main(int argc, char **argv, char **envp)
{
    char *rl = NULL;
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

        // Passer en mode non-interactif avant d'exécuter la commande
        set_signals_noninteractive();

        // Traiter la commande
        data->exit_status = process_command(rl, data);

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