/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/02 15:10:25 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Vérifie si un identifiant est valide pour une variable d'environnement
 */
int	is_valid_identifier_exp(char *id)
{
	int	i;

	if (!id || !*id)
		return (0);
	if (!ft_isalpha(id[0]) && id[0] != '_')
		return (0);
	i = 1;
	while (id[i])
	{
		if (!ft_isalnum(id[i]) && id[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Traite un argument spécifique d'export
 */
int	process_export_arg(char *arg, t_env_list **env_list)
{
	char	*error_msg;

	if (ft_strchr(arg, '=') != NULL)
		return (process_export_with_equals(arg, env_list));
	if (!is_valid_identifier_exp(arg))
	{
		error_msg = ft_strjoin(arg, ": not a valid identifier");
		error_handler("export", error_msg, 0, 1);
		free(error_msg);
		return (EXIT_FAILURE);
	}
	if (!get_env_var(*env_list, arg))
		add_env_var(env_list, arg, "");
	return (EXIT_SUCCESS);
}

/**
 * Implémente la commande builtin 'export'
 */
int	builtin_export(t_cmd *command, t_env_list **env_list)
{
	int	i;
	int	status;

	if (command->args[1] == NULL)
	{
		print_export_list(*env_list);
		return (EXIT_SUCCESS);
	}
	status = EXIT_SUCCESS;
	i = 1;
	while (command->args[i])
	{
		if (process_export_arg(command->args[i], env_list) == EXIT_FAILURE)
			status = EXIT_FAILURE;
		i++;
	}
	return (status);
}
