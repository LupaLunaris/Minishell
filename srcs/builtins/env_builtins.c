/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:22:25 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/09 13:51:07 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Display all environment variables without any arguments */
int	builtin_env(t_cmd *cmd, t_env_list **env_list)
{
	if (cmd->args[1] != NULL)
		return (error_handler("env", "too many arguments", 0, EXIT_FAILURE));
	if (!env_list)
		return (error_handler("env",
				"environment not available", 0, EXIT_FAILURE));
	print_env_list(*env_list);
	return (EXIT_SUCCESS);
}
