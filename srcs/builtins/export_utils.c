/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:34:49 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/09 13:52:19 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Display environment variables in 'export' command format */
void	print_export_list(t_env_list *env_list)
{
	t_env_list	**sorted_env;
	int			count;
	int			i;

	count = count_env_vars(env_list);
	sorted_env = malloc(sizeof(t_env_list *) * (count + 1));
	if (!sorted_env)
		return ;
	i = 0;
	while (env_list)
	{
		sorted_env[i++] = env_list;
		env_list = env_list->next;
	}
	sorted_env[i] = NULL;
	sort_env_list(sorted_env, count);
	print_sorted_exp(sorted_env, count);
	free(sorted_env);
}

/* Handle export command error with invalid identifier */
int	export_error(char *name)
{
	char	*error_msg;

	error_msg = ft_strjoin(name, ": not a valid identifier");
	error_handler("export", error_msg, 0, 1);
	free(error_msg);
	free(name);
	return (EXIT_FAILURE);
}

/* Process export argument containing an equals sign */
int	process_export_with_equals(char *arg, t_env_list **env_list)
{
	char	*name;
	char	*value;
	char	*equals_pos;

	equals_pos = ft_strchr(arg, '=');
	name = ft_substr(arg, 0, equals_pos - arg);
	if (!name)
		return (EXIT_FAILURE);
	if (!is_valid_identifier(name))
		return (export_error(name));
	value = ft_strdup(equals_pos + 1);
	if (!value)
	{
		free(name);
		return (EXIT_FAILURE);
	}
	update_env_var(env_list, name, value);
	free(name);
	free(value);
	return (EXIT_SUCCESS);
}

/* Display sorted environment variables for export command */
void	print_sorted_exp(t_env_list **sorted_env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("declare -x %s", sorted_env[i]->key);
		if (sorted_env[i]->value && ft_strlen(sorted_env[i]->value) > 0)
			printf("=\"%s\"", sorted_env[i]->value);
		printf("\n");
		i++;
	}
}
