/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:01:14 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/25 14:14:18 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Dans ta structure t_cmd, ajoute:
bool pipe_output;  // true si cette commande pipe vers la suivante

// Fonction de fermeture des pipes
void close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd)
{
    while (cmds)
    {
        if (cmds != skip_cmd && cmds->pipe_fd[0] != -1)
        {
            close(cmds->pipe_fd[0]);
            cmds->pipe_fd[0] = -1;
        }
        if (cmds != skip_cmd && cmds->pipe_fd[1] != -1)
        {
            close(cmds->pipe_fd[1]);
            cmds->pipe_fd[1] = -1;
        }
        cmds = cmds->next;
    }
}

// Création des pipes
bool create_pipes(t_cmd *cmd_list)
{
    t_cmd *curr = cmd_list;
    
    while (curr)
    {
        curr->pipe_fd[0] = -1;
        curr->pipe_fd[1] = -1;
        
        // Crée un pipe si cette commande a besoin d'être connectée (entrée ou sortie)
        if (curr->pipe_output || (curr->prev && curr->prev->pipe_output))
        {
            if (pipe(curr->pipe_fd) == -1)
            {
                perror("pipe");
                return false;
            }
            printf("un pipe est creer pour la commande %p\n", (void*)curr);
        }
        curr = curr->next;
    }
    return true;
}

// Configuration des descripteurs de pipes
void setup_pipes(t_cmd *cmd_list, t_cmd *curr)
{
    if (!curr)
        return;
    
    printf("Configuration pipes pour cmd %p\n", (void*)curr);
    
    // Redirection de l'entrée si nécessaire (commande précédente pipée vers celle-ci)
    if (curr->prev && curr->prev->pipe_output && !curr->input_file)
    {
        printf("  Redirection STDIN depuis pipe précédent\n");
        dup2(curr->prev->pipe_fd[0], STDIN_FILENO);
    }
    
    // Redirection de la sortie si nécessaire (cette commande pipée vers la suivante)
    if (curr->pipe_output && !curr->output_file)
    {
        printf("  Redirection STDOUT vers pipe\n");
        dup2(curr->pipe_fd[1], STDOUT_FILENO);
    }
    
    // Fermeture de tous les autres descripteurs de pipe
    close_pipe_fds(cmd_list, curr);
}

// /* setup_pipes:
//  * Configure les entrées/sorties des pipes pour une commande
//  */
// static void setup_pipes(t_command *cmd_list, t_command *curr)
// {
//     if (!curr)
//         return;
//     // Si commande précédente existe et a un pipe, connecter son pipe à l'entrée
//     if (curr->prev && curr->prev->pipe_fd[0] != -1 && !curr->input_file)
//         dup2(curr->prev->pipe_fd[0], STDIN_FILENO);

//     // Si pipé à une commande suivante, connecter sa sortie au pipe
//     if (curr->next && curr->pipe_fd[1] != -1 && !curr->output_file)
//         dup2(curr->pipe_fd[1], STDOUT_FILENO);

//     // Fermer tous les pipes inutiles
//     t_command *tmp = cmd_list;
//     while (tmp)
//     {
//         if (tmp->pipe_fd[0] != -1 && 
//             (tmp != curr || (curr->prev && curr->prev->pipe_fd[0] != curr->pipe_fd[0])))
//             close(tmp->pipe_fd[0]);
//         if (tmp->pipe_fd[1] != -1 && 
//             (tmp != curr || (curr->next && curr->next->pipe_fd[1] != curr->pipe_fd[1])))
//             close(tmp->pipe_fd[1]);
//         tmp = tmp->next;
//     }
// }

// /* create_pipes:
//  * Crée les pipes pour les commandes chaînées
//  */
// static bool create_pipes(t_command *cmd_list)
// {
//     t_command *curr = cmd_list;
    
//     while (curr)
//     {
//         curr->pipe_fd[0] = -1;
//         curr->pipe_fd[1] = -1;
//         // Crée un pipe si nécessaire (s'il y a une commande suivante)
//         if (curr->next)
//         {
//             if (pipe(curr->pipe_fd) == -1)
//             {
//                 perror("pipe");
//                 return (false);
//             }
//         }
//         curr = curr->next;
//     }
//     return true;
// }

// /* close_all_pipes:
//  * Ferme tous les pipes
//  */
// static void close_all_pipes(t_command *cmd_list)
// {
//     t_command *curr = cmd_list;
    
//     while (curr)
//     {
//         if (curr->pipe_fd[0] != -1)
//             close(curr->pipe_fd[0]);
//         if (curr->pipe_fd[1] != -1)
//             close(curr->pipe_fd[1]);
//         curr = curr->next;
//     }
// }

// /* execute_piped_cmd:
//  * Exécute une commande dans un pipeline
//  */
// static void execute_piped_cmd(t_command *cmd, t_command *cmd_list, 
//                             t_env_list *env_list, t_shell_data *data)
// {
//     // Configure les redirections et pipes
//     setup_redirection(cmd->input_file, cmd->output_file, cmd->append);
//     setup_pipes(cmd_list, cmd);
//     // Exécute la commande
//     if (cmd->is_builtin)
//     {
//         int status = execute_builtin(cmd, data);
//         exit(status);
//     }
//     else
//     {
//         execute_command(cmd, env_list);
//         // execute_command appelle déjà exit en interne si nécessaire
//     }
// }

// /* execute_pipeline:
//  * Exécute une série de commandes liées par des pipes
//  */
// int execute_pipeline(t_command *cmd, t_env_list *env_list, t_shell_data *data)
// {
//     bool has_pipe = false;
//     t_command *curr = cmd;
    
//     // Vérifie si une commande dans la liste est reliée par pipe
//     while (curr)
//     {
//         if (curr->next)
//         {
//             has_pipe = true;
//             break;
//         }
//         curr = curr->next;
//     }
//     // Si pas de pipe et builtin, exécution directe
//     if (!has_pipe && cmd->is_builtin)
//     {
//         setup_redirection(cmd->input_file, cmd->output_file, cmd->append);
//         int status = execute_builtin(cmd, data);
//         restore_io(cmd->input_file, cmd->output_file);
//         return status;
//     }
//     // Crée les pipes nécessaires
//     if (!create_pipes(cmd))
//         return EXIT_FAILURE;    
//     // Crée un processus pour chaque commande
//     curr = cmd;
//     while (curr)
//     {
//         pid_t pid = fork();
//         if (pid == -1)
//         {
//             perror("fork");
//             close_all_pipes(cmd);
//             return EXIT_FAILURE;
//         }
//         if (pid == 0) // Processus enfant
//             execute_piped_cmd(curr, cmd, env_list, data);
//         curr->pid = pid;
//         curr = curr->next;
//     }
//     // Ferme tous les pipes dans le processus parent
//     close_all_pipes(cmd);
//     // Attendre la fin des processus enfants
//     return get_children(cmd);
// }
