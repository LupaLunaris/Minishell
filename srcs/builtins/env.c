/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:22:25 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/20 14:36:14 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int builtin_env(char **args, t_env_list *env_list)
{
    int i = 1;
    // Si des options sont spécifiées (comme "env -u"), ou des configurations (VAR=value), gère-les
    while (args[i])
    {
        if (!ft_strcmp(args[i], "-u")) // Exemple : option "-u" (unset variable)
        {
            i++;
            if (args[i]) // Variable à supprimer
                unset_env_var(env_list, args[i]); // Fonction qui supprime une variable de l'env
            else
                return (EXIT_FAILURE); // Retourne une erreur si aucun varname
        }
        else if (ft_strchr(args[i], '=')) // Exemple : VAR=value
        {
            add_env_var(env_list, args[i]); // Fonction qui ajoute/modifie une variable d'environnement
        }
        else
        {
            // Si un argument non reconnu est passé, retourne une erreur
            write(STDERR_FILENO, "env: illegal option or argument\n", 32);
            return (EXIT_FAILURE);
        }
        i++;
    }
    // Si aucun argument spécifique, affiche uniquement les variables d'environnement
    print_env_list(env_list); // Fonction print (liste chaînée représentant l'environnement)
    return (EXIT_SUCCESS);
}
