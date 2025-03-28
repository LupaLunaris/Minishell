/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:14:54 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/28 10:34:09 by Jpaulis          ###   ########.fr       */
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

t_env_list *init_env(char **envp)
{
    t_env_list *head = NULL;
    t_env_list *node;
    t_env_list *temp;
    int i = 0;

    while (envp[i])
    {
        node = malloc(sizeof(t_env_list));
        if (!node)
        {
            free_env_list(head);
            return (NULL);
        }
        char **key_value = ft_split(envp[i], '=');
        node->key = strdup(key_value[0]);
        node->value = strdup(key_value[1]);
        node->next = NULL;
        if (!head)
            head = node;
        else
        {
            temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = node;
        }
        free_split(key_value);
        i++;
    }
    return (head);
}
