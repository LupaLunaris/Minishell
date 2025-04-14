/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:40:04 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/09 13:53:20 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Implement the 'pwd' builtin command to print working directory */
int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		error_handler("pwd", "unable to get current directory", 0, 1);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (EXIT_SUCCESS);
}
