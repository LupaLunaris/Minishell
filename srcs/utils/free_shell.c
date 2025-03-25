/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:14:57 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/19 15:16:20 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env_list(t_env_list *env_list) {
    t_env_list *tmp;

    while (env_list) {
        tmp = env_list;
        env_list = env_list->next;
        // Libère les champs de la structure t_env_list
        if (tmp->key)
            free(tmp->key);
        if (tmp->value)
            free(tmp->value);
        // Libère la structure elle-même
        free(tmp);
    }
}

void free_shell_data(t_shell_data *data) {
    if (!data)
        return;
    // Libère la liste chaînée des variables d'environnement
    if (data->env_list)
        free_env_list(data->env_list);
    // Libère l'historique des commandes
    free(data);
}

void    free_command(t_cmd *cmd)
{
    t_cmd *tmp;

    while (cmd)
	{
        tmp = cmd->next;
        // Libère les champs alloués dynamiquement
        if (cmd->cmd)
            free(cmd->cmd);
        if (cmd->args)
		{
            for (int i = 0; cmd->args[i]; i++)
                free(cmd->args[i]);
            free(cmd->args);
        }
        if (cmd->input_file)
            free(cmd->input_file);
        if (cmd->output_file)
            free(cmd->output_file);
        if (cmd->heredoc)
            free(cmd->heredoc);
        // Libère le maillon actuel
        free(cmd);
        // Passe au suivant
        cmd = tmp;
    }
}