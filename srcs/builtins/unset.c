/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:02:36 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/12 16:07:21 by Jpaulis          ###   ########.fr       */
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
int is_valid_identifier(char *str)
{
    int i;

    // Vérification de paramètre NULL
    if (!str || !*str)
        return (0);
    // Premier caractère: lettre ou underscore uniquement
    if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);

    // Caractères suivants: lettres, chiffres ou underscore
    i = 1;
    while (str[i])
    {
        if (!(ft_isalnum(str[i]) || str[i] == '_' ||  str[i] == '=' )) // j'ai rajouter le =
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
int builtin_unset(char **args, t_env_list **env_list)
{
	int i;      // Index pour parcourir les arguments
	int status; // Code de retour de la commande

	i = 1;      // Commencer à l'argument 1 (après "unset")
	status = 0; // Par défaut, pas d'erreur
	// Si pas d'arguments, on ne fait rien et on retourne 0
	if (!args[1])
		return (0);
	// Parcourir tous les arguments
	while (args[i])
	{
		// Vérifier si l'identifiant est valide
		if (!is_valid_identifier(args[i]))
		{
			// Afficher message d'erreur sur stderr
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1; // Mettre le statut d'erreur
		}
		else
			// Supprimer la variable de l'environnement si l'identifiant est valide
			delete_env_var(env_list, args[i]);
		i++; // Passer à l'argument suivant
	}
	// Retourner le statut final (0 si tout s'est bien passé, 1 sinon)
	return (status);
}
