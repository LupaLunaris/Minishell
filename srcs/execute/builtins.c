/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:02:55 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/19 14:03:09 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int is_builtin(char *cmd) {
    return (!strcmp(cmd, "echo") || !strcmp(cmd, "cd") || !strcmp(cmd, "pwd") || 
            !strcmp(cmd, "export") || !strcmp(cmd, "unset") || !strcmp(cmd, "env") || 
            !strcmp(cmd, "exit"));
}

void execute_builtin(t_command *cmd) {
    if (!strcmp(cmd->cmd, "echo")) {
        // Implémente echo
    } else if (!strcmp(cmd->cmd, "cd")) {
        // Implémente cd
    }
    // Ajoute d'autres builtins ici
}
