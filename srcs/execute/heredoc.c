/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:44:57 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/30 17:09:13 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Lit les entrées jusqu'au délimiteur et les stocke dans le contenu du heredoc
 * Renvoie 0 en cas de succès, un code d'erreur sinon
 */
static int read_heredoc_content(char *delimiter, char **content)
{
    char *line;
    char *temp;
    char *new_content = ft_strdup("");
    
    if (!new_content)
        return (error_handler("heredoc", "memory allocation failed", 0, 1));

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            free(new_content);
            return (error_handler("heredoc", 
                "unexpected EOF while looking for heredoc delimiter", 0, 130));
        }
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        
        // Ajouter la ligne au contenu du heredoc
        temp = new_content;
        new_content = ft_strjoin(new_content, line);
        free(temp);
        free(line);
        
        if (!new_content)
            return (error_handler("heredoc", "memory allocation failed", 0, 1));
            
        // Ajouter un saut de ligne
        temp = new_content;
        new_content = ft_strjoin(new_content, "\n");
        free(temp);
        
        if (!new_content)
            return (error_handler("heredoc", "memory allocation failed", 0, 1));
    }
    
    *content = new_content;
    return (0);
}

/**
 * Configure le heredoc pour une commande
 * Lit l'entrée et la stocke dans cmd->heredoc
 * Renvoie 0 en cas de succès, un code d'erreur sinon
 */
int process_heredoc(char *delimiter, t_cmd *command)
{
    char *content = NULL;
    int status;

    status = read_heredoc_content(delimiter, &content);
    if (status != 0)
        return (status);
        
    // Stocker le contenu du heredoc dans la commande
    if (command->heredoc)
        free(command->heredoc);
    command->heredoc = content;
    
    return (0);
}

/**
 * Traite tous les heredocs dans une pipeline
 * Renvoie 0 si tout s'est bien passé, un code d'erreur sinon
 */
int setup_heredocs_for_pipeline(t_cmd *cmd_list)
{
    t_cmd *current;
    int status;

    current = cmd_list;
    while (current)
    {
        if (current->heredoc && ft_strlen(current->heredoc) == 0) // C'est un délimiteur, pas encore le contenu
        {
            status = process_heredoc(current->heredoc, current);
            if (status != 0)
                return (status);
        }
        current = current->next;
    }
    
    return (0);
}
