/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:03:59 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 19:36:20 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_cmd(t_cmd *cmd)
{
    if (!cmd)
    {
        printf("Command is NULL.\n");
        return;
    }
    printf("Command name: %s\n", cmd->cmd);
    if (cmd->args)
    {
        printf("Arguments:\n");
        for (int i = 0; cmd->args[i]; i++) {
            printf("  - %s\n", cmd->args[i]);
        }
    }
    
    // Afficher les redirections
    t_redirection *redir = cmd->redirections;
    while (redir)
    {
        switch (redir->type)
        {
            case REDIR_INPUT:
                printf("Input redirection: %s\n", redir->file);
                break;
            case REDIR_OUTPUT:
                printf("Output redirection: %s\n", redir->file);
                break;
            case REDIR_APPEND:
                printf("Append redirection: %s\n", redir->file);
                break;
            case REDIR_HEREDOC:
                printf("Heredoc redirection\n");
                break;
            default:
                printf("Unknown redirection type: %d\n", redir->type);
        }
        redir = redir->next;
    }
}
