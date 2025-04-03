/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expend2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:45:41 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/02 22:01:04 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction pour développer les variables d'environnement*/
char *expand_variables(char *str, t_env_list *list, t_shell_data *data)
{
	char *result;
	int i;
	int j;
	int in_squote;
	int in_dquote;

	in_squote = 0;
	in_dquote = 0;
	if (!str)
		return (NULL);
	int has_quotes = 0;
	for (i = 0; str[i]; i++) {
		if (str[i] == '\'' || str[i] == '"') {
			has_quotes = 1;
			break ;
		}
	}
	if (!has_quotes)
	{
		result = malloc(4096);
		if (!result)
			return (NULL);
		i = 0;
		j = 0;
		while (str[i])
		{
			if (str[i] == '$' && str[i+1])
			{
				i++;
				if (str[i] == '?')
				{
					char *exit_str = ft_itoa(data->exit_status);
					int k = 0;
					while (exit_str[k])
						result[j++] = exit_str[k++];
					free(exit_str);
					i++;
				}
				else if (str[i] == '$')
				{
					char *pid_str = ft_itoa(getpid());
					int k = 0;
					while (pid_str[k])
						result[j++] = pid_str[k++];
					free(pid_str);
					i++;
				}
				else if (ft_isalpha(str[i]) || str[i] == '_')
				{
					int start = i;
					while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
						i++;
					char *var_name = ft_substr(str, start, i - start);
					char *var_value = get_env_value(list, var_name);
					if (var_value)
					{
						int k = 0;
						while (var_value[k])
							result[j++] = var_value[k++];
					}
					free(var_name);
				}
				else
					result[j++] = '$';
			}
			else
				result[j++] = str[i++];
		}
		result[j] = '\0';
		char *final_result = ft_strdup(result);
		free(result);
		return (final_result);
	}
	result = malloc(4096);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dquote)
		{
			in_squote = !in_squote;
			i++;
		}
		else if (str[i] == '"' && !in_squote)
		{
			in_dquote = !in_dquote;
			i++;
		}
		else if (str[i] == '$' && str[i+1] && !in_squote)
		{
			i++;
			if (str[i] == '?')
			{
				char *exit_str = ft_itoa(data->exit_status);
				int k = 0;
				while (exit_str[k])
					result[j++] = exit_str[k++];
				free(exit_str);
				i++;
			}
			else if (str[i] == '$')
			{
				char *pid_str = ft_itoa(getpid());
				int k = 0;
				while (pid_str[k])
					result[j++] = pid_str[k++];
				free(pid_str);
				i++;
			}
			// Expansions des variables d'environnement
			else if (ft_isalpha(str[i]) || str[i] == '_')
			{
				int start = i;
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;

				char *var_name = ft_substr(str, start, i - start);
				char *var_value = get_env_value(list, var_name);

				if (var_value)
				{
					int k = 0;
					while (var_value[k])
						result[j++] = var_value[k++];
				}
				free(var_name);
			}
			else
				result[j++] = '$';
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	char *final_result = ft_strdup(result);
	free(result);
	return (final_result);
}
