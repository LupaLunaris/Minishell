/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   env_init.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: Jpaulis <Jpaulis@student.s19.be>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/12 16:18:45 by Jpaulis		   #+#	#+#			 */
/*   Updated: 2025/03/12 16:20:11 by Jpaulis		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

/**
 * Initialise la liste d'environnement à partir du envp
 * @param envp Le tableau d'environnement fourni au programme
 * @return Un pointeur vers la liste chaînée des variables d'environnement
 */
t_env_list	*init_env(char **envp)
{
	t_env_list	*env_list;
	int			i;
	char		*key;
	char		*value;
	char		*equals_pos;

	i = 0;
	env_list = NULL;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		equals_pos = ft_strchr(envp[i], '=');
		if (equals_pos)
		{
			key = ft_substr(envp[i], 0, equals_pos - envp[i]);
			value = ft_strdup(equals_pos + 1);
			if (key && value)
				add_env_var(&env_list, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (env_list);
}

t_quote	*init_quote_state(void)
{
	t_quote	*state;

	state = malloc(sizeof(t_quote));
	state->in_squote = 0;
	state->in_dquote = 0;
	return (state);
}

char	*expand_variables(char *str, t_shell_data *data)
{
	char	*result;
	char	*final_result;

	data->state = init_quote_state();
	if (!str)
		return (NULL);
	result = malloc(4096);
	if (!result)
		return (NULL);
	if (!has_quotes(str))
	{
		final_result = expand_no_quote(str, result, data);
		return (final_result);
	}
	final_result = expand_quote(str, result, data);
	return (final_result);
}

char	*init_expand_result(char *str, t_shell_data *data)
{
	char	*result;

	if (!str)
		return (NULL);
	data->state = init_quote_state();
	result = malloc(4096);
	return (result);
}

void	expand_cmd_args(t_cmd *cmd, t_shell_data *data)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_variables(cmd->args[i], data);
		if (expanded)
		{
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
}
