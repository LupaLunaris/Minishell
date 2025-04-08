/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   var_expend.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: Jpaulis <Jpaulis@student.s19.be>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/28 10:17:19 by Jpaulis		   #+#	#+#			 */
/*   Updated: 2025/04/02 12:49:27 by Jpaulis		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

char	*expand_no_quote(char *str, char *result, t_shell_data *data)
{
	t_indices	idx;
	char		*final_result;

	idx.i = 0;
	idx.j = 0;
	while (str[idx.i])
	{
		if (str[idx.i] == '$' && str[idx.i + 1])
		{
			idx.i++;
			idx = process_special_vars(str, result, data, idx);
		}
		else
			result[idx.j++] = str[idx.i++];
	}
	result[idx.j] = '\0';
	final_result = ft_strdup(result);
	free(result);
	return (final_result);
}

t_indices	process_quoted_vars(char *str, char *result, t_shell_data *data,
	t_indices idx)
{
	t_indices	n_id;
	int			quote_changed;

	n_id = idx;
	quote_changed = 0;
	n_id = is_in_squote(data->state, str, n_id);
	if (n_id.i > idx.i)
		quote_changed = 1;
	if (!quote_changed && str[n_id.i] == '$' && str[n_id.i + 1]
		&& !data->state->in_squote)
	{
		n_id.i++;
		n_id = process_special_vars(str, result, data, n_id);
	}
	else if (!quote_changed)
		result[n_id.j++] = str[n_id.i++];
	return (n_id);
}

char	*expand_quote(char *str, char *result, t_shell_data *data)
{
	t_indices	idx;
	char		*final_result;

	idx.i = 0;
	idx.j = 0;
	while (str[idx.i])
		idx = process_quoted_vars(str, result, data, idx);
	result[idx.j] = '\0';
	final_result = ft_strdup(result);
	free(result);
	return (final_result);
}

int	handle_none_var(t_env_list *list, t_cmd *cmd, t_shell_data *data)
{
	int	j;

	if (!cmd->args[0] || cmd->args[0][0] != '$')
		return (0);
	if (is_none_var(list, cmd))
	{
		if (cmd->args[1])
		{
			free(cmd->args[0]);
			j = 0;
			while (cmd->args[j + 1])
			{
				cmd->args[j] = cmd->args[j + 1];
				j++;
			}
			cmd->args[j] = NULL;
			free(cmd->cmd);
			cmd->cmd = ft_strdup(cmd->args[0]);
		}
		else
			data->exit_status = 127;
		return (1);
	}
	return (0);
}

void	var_expend(t_env_list *list, t_cmd *cmds, t_shell_data *data)
{
	t_cmd	*cmd_temp;

	cmd_temp = cmds;
	while (cmd_temp)
	{
		if (cmd_temp->args)
		{
			if (!handle_none_var(list, cmd_temp, data))
				expand_cmd_args(cmd_temp, data);
		}
		update_cmd_from_args(cmd_temp);
		cmd_temp = cmd_temp->next;
	}
}
