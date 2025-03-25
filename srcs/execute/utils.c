/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:03:59 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/19 15:16:13 by Jpaulis          ###   ########.fr       */
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
    if (cmd->input_file)
        printf("Input redirection: %s\n", cmd->input_file);
    if (cmd->output_file)
        printf("Output redirection: %s\n", cmd->output_file);
}
