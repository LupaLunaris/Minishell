/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:21:37 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/17 13:59:06 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Implémente la commande builtin 'cd'
 * Gère les chemins relatifs et absolus
 */
int	builtin_cd(char **args, t_list **env_list)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*path;

	// Sauvegarde du répertoire courant (pour OLDPWD)
	if (getcwd(old_pwd, PATH_MAX) == NULL)
		return (error_handler("cd", strerror(errno), 0, 1));
	// Cas 1: cd sans argument (aller au HOME)
	if (args[1] == NULL)
	{
		path = get_env_value(*env_list, "HOME");
		if (path == NULL)
			return (error_handler("cd", "HOME not set", 0, 1));
	}
	// Cas 2: cd avec un chemin (absolu ou relatif)
	else
		path = args[1];
	// Changement de répertoire
	if (chdir(path) == -1)
		return (error_handler("cd", strerror(errno), 0, 1));
	// Mise à jour du PWD actuel après le changement
	if (getcwd(new_pwd, PATH_MAX) == NULL)
		return (error_handler("cd", strerror(errno), 0, 1));
	// Mise à jour des variables d'environnement
	update_env_var(env_list, "OLDPWD", old_pwd);
	update_env_var(env_list, "PWD", new_pwd);
	return (0);
}
