/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_verif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:01:57 by malafont          #+#    #+#             */
/*   Updated: 2025/04/07 10:02:01 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	handle_q_mark(t_shell_data *data, char *result, int j, int i)
{
	int		k;
	char	*exit_str;

	k = 0;
	i++;
	exit_str = ft_itoa(data->exit_status);
	while (exit_str[k])
		result[j++] = exit_str[k++];
	free(exit_str);
	return (j);
}

int	handle_dollars(char *result, int j, int i)
{
	int		k;
	char	*pid_str;

	i++;
	k = 0;
	pid_str = ft_itoa(getpid());
	while (pid_str[k])
		result[j++] = pid_str[k++];
	free(pid_str);
	return (j);
}

t_indices	is_in_squote(t_quote *state, char *str, t_indices idx)
{
	if (str[idx.i] == '\'' && !state->in_dquote)
	{
		state->in_squote = !state->in_squote;
		idx.i++;
		return (idx);
	}
	else if (str[idx.i] == '"' && !state->in_squote)
	{
		state->in_dquote = !state->in_dquote;
		idx.i++;
		return (idx);
	}
	return (idx);
}

int	is_none_var(t_env_list *list, t_cmd *cmd)
{
	if (cmd->args[0][0] == '$'
		&& (cmd->args[0][1] == '$'
			|| cmd->args[0][1] == '?'))
		return (0);
	if (!get_env_var(list, cmd->args[0] + 1)
		|| (get_env_var(list, cmd->args[0] + 1)
			&& ft_strlen(get_env_var(list, cmd->args[0] + 1)) == 0))
		return (1);
	return (0);
}
