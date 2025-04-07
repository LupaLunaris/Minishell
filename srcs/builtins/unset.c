/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:02:36 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/02 15:05:16 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Vérifie si une chaîne est un identifiant valide selon les règles POSIX
 * Un identifiant valide :
 * - Doit commencer par une lettre (a-z, A-Z) ou un underscore (_)
 * - Ne peut contenir que des lettres, chiffres et underscores
 *
 * @param str La chaîne à vérifier
 * @return 1 si l'identifiant est valide, 0 sinon
 */
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

/**
 * Commande intégrée 'unset' - Supprime les variables d'environnement
 * @param args     Tableau d'arguments (args[0] est "unset")
 * @param env_list Pointeur sur la liste des variables d'environnement
 * @return         0 en cas de succès, 1 en cas d'erreur
 */
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
