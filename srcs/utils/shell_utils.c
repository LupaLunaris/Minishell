/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:40:21 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/08 15:09:33 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction principale de la boucle du shell */
void	main_shell_loop(t_shell_data *data, char **rl)
{
	while (1)
	{
		g_signal_received = 0;
		if (data->interactive)
			set_signals_interactive();
		handle_input_loop(data, rl);
		if (*rl == NULL || data->should_exit)
			break ;
	}
}

/* Traite les redirections pour une liste de commandes */
int	process_all_redirections(t_cmd *cmd_list)
{
	t_cmd			*curr;
	t_redirection	*redir;
	int				status;

	curr = cmd_list;
	while (curr)
	{
		redir = curr->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				status = process_heredoc(redir->file, curr);
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
	return (0);
}

/* Gère les erreurs d'initialisation d'environnement */
int	error_message_env_init(t_shell_data *data)
{
	free(data);
	return (error_handler("init_env", "Failed to init env vars", 1,
			EXIT_FAILURE));
}

/* Affiche un message d'erreur pour la mémoire et sort */
int	error_message_and_exit(char *prefix, char *message)
{
	return (error_handler(prefix, message, 1, EXIT_FAILURE));
}

t_shell_data	*init_shell_data(char **envp)
{
	t_shell_data	*data;

	data = malloc(sizeof(t_shell_data));
	if (!data)
		return (NULL);
	data->exit_status = 0;
	data->interactive = isatty(STDIN_FILENO);
	data->env_list = init_env(envp);
	data->state = NULL;
	data->should_exit = 0;
	return (data);
}
