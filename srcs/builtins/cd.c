/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:21:37 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 21:32:06 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_cd(char **args, t_env_list **env_list)
{
    char old_pwd[PATH_MAX];
    char new_pwd[PATH_MAX];
    char *path;
    
    // Vérification du nombre d'arguments
    if (args[1] != NULL && args[2] != NULL)
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return (1);
    }
    
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
    // Cas 2: cd - (retour au répertoire précédent)
    else if (ft_strcmp(args[1], "-") == 0)
    {
        path = get_env_value(*env_list, "OLDPWD");
        if (path == NULL)
            return (error_handler("cd", "OLDPWD not set", 0, 1));
        
        // Afficher le répertoire vers lequel on se déplace
        ft_putendl_fd(path, 1);
    }
    // Cas 3: cd avec un chemin (absolu ou relatif)
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
