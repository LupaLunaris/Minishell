/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:17:31 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/28 11:09:58 by Jpaulis          ###   ########.fr       */
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

void handle_signals_and_input(t_shell_data *data, char **rl, int *final_status)
{
    *rl = readline("MiniShellDeLaMort> ");
    
    if (*rl == NULL)
    {
        if (data->interactive)
            write(STDOUT_FILENO, "exit\n", 5);
        *final_status = data->exit_status;
        return;
    }

    if ((*rl)[0] != '\0')
        add_history(*rl);

    set_signals_noninteractive();
}

void execute_user_command(t_shell_data *data, const char *rl)
{
    char **splited_args;
    t_cmd *cmds;

    splited_args = ft_split(rl, ' ');
    if (!splited_args)
        return;

    cmds = parser(splited_args);
    if (!cmds)
    {
        free_arr(splited_args); // Utilisation de free_arr au lieu de free_split
        return;
    }

    var_expend(data->env_list, cmds); // Utilisation du nom correct de ta fonction

    add_builtin(cmds);
    data->exit_status = execute(cmds, data->env_list, data);

    free_command(cmds);
    free_arr(splited_args); // Utilisation de free_arr au lieu de free_split

    if (g_signal_received == SIGINT)
        data->exit_status = 130;
    else if (g_signal_received == SIGQUIT)
        data->exit_status = 131;
}

int main(int argc, char **argv, char **envp)
{
    t_shell_data *data;
    int final_status = 0;
    char *rl = NULL;

    if (argc != 1 || !argv)
        return 1;

    data = init_shell_data(envp); // Utilisation du nom correct
    if (!data)
        return 1;

    while (1)
    {
        g_signal_received = 0;
        if (data->interactive)
            set_signals_interactive();

        handle_signals_and_input(data, &rl, &final_status);
        if (final_status)
            break;
        
        if (rl)
        {
            execute_user_command(data, rl);
            free(rl);
            rl = NULL;
        }
    }
    
    free_shell_data(data); // Utilisation du nom correct pour nettoyer les ressources
    return (final_status);
}
