/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:59:33 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/08 15:22:27 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_array(char **env_array)
{
	int	i;

	i = 0;
	if (!env_array)
		return;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}
