/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:17:19 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/02 22:01:52 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction principale pour développer les variables
void	var_expend(t_env_list *list, t_cmd *cmds, t_shell_data *data)
{
	t_cmd	*cmd_temp;
	int		j;
	int		i;

	cmd_temp = cmds;
	while (cmd_temp)
	{
		if (cmd_temp->args)
		{
			i = 0;
			if (cmd_temp->args[0] && cmd_temp->args[0][0] == '$' && 
				(!get_env_var(list, cmd_temp->args[0] + 1) || 
				 (get_env_var(list, cmd_temp->args[0] + 1) && ft_strlen(get_env_var(list, cmd_temp->args[0] + 1)) == 0)))
			{
				if (cmd_temp->args[1])
				{
					free(cmd_temp->args[0]);
					j = 0;
					while (cmd_temp->args[j+1])
					{
						cmd_temp->args[j] = cmd_temp->args[j+1];
						j++;
					}
					cmd_temp->args[j] = NULL;
					free(cmd_temp->cmd);
					cmd_temp->cmd = ft_strdup(cmd_temp->args[0]);
				}
				else
					data->exit_status = 127;
			}
			else
			{
				while (cmd_temp->args[i])
				{
					char *expanded = expand_variables(cmd_temp->args[i], list, data);
					if (expanded)
					{
						free(cmd_temp->args[i]);
						char *no_quotes = remove_quotes(expanded);
						free(expanded);
						cmd_temp->args[i] = no_quotes;
					}
					i++;
				}
			}
		}
		if (cmd_temp->args && cmd_temp->args[0])
		{
			free(cmd_temp->cmd);
			cmd_temp->cmd = ft_strdup(cmd_temp->args[0]);
		}
		cmd_temp = cmd_temp->next;
	}
}
