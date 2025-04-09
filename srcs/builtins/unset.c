/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:02:36 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/09 13:53:46 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if a string is a valid POSIX identifier */
int	is_valid_identifier(char *arg)
{
	int		i;
	char	*equals_pos;

	if (!arg || !*arg)
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	equals_pos = ft_strchr(arg, '=');
	i = 0;
	while (arg[i] && (!equals_pos || &arg[i] < equals_pos))
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* Implement the 'unset' builtin command to remove environment variables */
int	builtin_unset(char **args, t_env_list **env_list)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!args[1])
		return (0);
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			delete_env_var(env_list, args[i]);
		i++;
	}
	return (status);
}
