/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:44:57 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 19:52:14 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Lit les entrées jusqu'au délimiteur et les stocke dans le contenu du heredoc
 * Renvoie 0 en cas de succès, un code d'erreur sinon
 */
static int read_heredoc_content(char *delimiter, char **content)
{
    // Cette fonction reste inchangée car elle prend un pointeur vers un contenu
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
 * Trouve une redirection heredoc qui utilise le délimiteur spécifié
 * Retourne la redirection ou NULL si aucune n'est trouvée
 */
t_redirection *find_heredoc_redirection(t_cmd *command, char *delimiter)
{
    t_redirection *redir = command->redirections;
    
    while (redir)
    {
        if (redir->type == REDIR_HEREDOC && ft_strcmp(redir->file, delimiter) == 0)
            return redir;
        redir = redir->next;
    }
    return NULL;
}
/**
 * Configure le heredoc pour une commande
 * Lit l'entrée et la stocke dans la redirection appropriée
 * Renvoie 0 en cas de succès, un code d'erreur sinon
 */
int process_heredoc(char *delimiter, t_cmd *command)
{
    t_redirection *redir = command->redirections;
    char *content = NULL;
    int status;
    
    // Trouver la redirection heredoc avec ce délimiteur
    while (redir)
    {
        if (redir->type == REDIR_HEREDOC && ft_strcmp(redir->file, delimiter) == 0)
            break;
        redir = redir->next;
    }
    
    if (!redir)
        return (0); // Pas de redirection heredoc avec ce délimiteur

    status = read_heredoc_content(delimiter, &content);
    if (status != 0)
        return (status);
    
    // Stocker le contenu du heredoc
    if (redir->heredoc_content)
        free(redir->heredoc_content);
    redir->heredoc_content = content;
    
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
    t_redirection *redir;

    current = cmd_list;
    while (current)
    {
        redir = current->redirections;
        while (redir)
        {
            if (redir->type == REDIR_HEREDOC && 
                (!redir->heredoc_content || ft_strlen(redir->heredoc_content) == 0))
            {
                // Appeler process_heredoc avec le bon nombre d'arguments et le bon type
                status = process_heredoc(redir->file, current);
                if (status != 0)
                    return (status);
            }
            redir = redir->next;
        }
        current = current->next;
    }
    
    return (0);
}
// Dans execute.c
char *get_heredoc_content(char *delimiter)
{
    char *content = NULL;
    char *line = NULL;
    char *temp;
    
    // Allouer un buffer vide initial
    content = ft_strdup("");
    if (!content)
        return (NULL);
    
    // Boucle de lecture des lignes jusqu'au délimiteur
    ft_putstr_fd("> ", STDOUT_FILENO);
    while (1)
    {
        line = readline("");
        if (!line) // EOF (Ctrl+D)
            break;
            
        // Si la ligne correspond au délimiteur, terminer
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        
        // Ajouter la ligne au contenu
        temp = ft_strjoin(content, line);
        free(content);
        free(line);
        content = temp;
        
        // Ajouter un retour à la ligne
        temp = ft_strjoin(content, "\n");
        free(content);
        content = temp;
        
        ft_putstr_fd("> ", STDOUT_FILENO);
    }
    
    return content;
}
