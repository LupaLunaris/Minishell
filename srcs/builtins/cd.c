/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:21:37 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/13 16:48:24 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/**
 * Gère spécifiquement la commande 'cd -' (retour au répertoire précédent)
 * Retourne le chemin vers lequel se déplacer ou NULL en cas d'erreur
 */
char *handle_cd_previous(t_env_list *env_list)
{
	char *path = get_env_value(env_list, "OLDPWD");
	
	if (!path || *path == '\0')
	{
		error_handler("cd", "OLDPWD not set", 0, 1);
		return (NULL);
	}
	// Afficher le chemin comme le fait bash
	printf("%s\n", path);
	return (path);
}

/**
 * Implémente la commande builtin 'cd'
 * Gère les chemins relatifs et absolus
 */
int builtin_cd(char **args, t_env_list **env_list)
{
	char *path;
	char old_pwd[PATH_MAX];
	
	// Sauvegarder le répertoire actuel
	if (getcwd(old_pwd, PATH_MAX) == NULL)
		return (error_handler("cd", strerror(errno), 0, 1));
	// Déterminer le chemin à utiliser
	if (!args[1])
	{
		// Aucun argument, aller au répertoire $HOME
		path = get_env_value(*env_list, "HOME");
		if (!path || *path == '\0')
			return (error_handler("cd", "HOME not set", 0, 1));
	}
	else if (strcmp(args[1], "-") == 0)
	{
		// Cas spécial: cd - (retour au répertoire précédent)
		path = handle_cd_previous(*env_list);
		if (!path)
			return (1);  // L'erreur a déjà été affichée
	}
	else
		// Utiliser le chemin fourni (relatif ou absolu)
		path = args[1];
	// Changer de répertoire
	if (chdir(path) == -1)
		return (error_handler("cd", strerror(errno), 0, 1));
	// Mettre à jour PWD et OLDPWD
	char new_pwd[PATH_MAX];
	if (getcwd(new_pwd, PATH_MAX) == NULL)
		return (error_handler("cd", strerror(errno), 0, 1));
	// Mettre à jour les variables d'environnement
	update_env_var(env_list, "OLDPWD", old_pwd);
	update_env_var(env_list, "PWD", new_pwd);
	return (0);
}
