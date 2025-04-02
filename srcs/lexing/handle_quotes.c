/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:33:29 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/02 12:40:32 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
** Fonction pour supprimer les guillemets des tokens tout en préservant
** les guillemets imbriqués.
*/
// Fonction pour supprimer les guillemets d'une chaîne en préservant les guillemets imbriqués
// Fonction pour supprimer uniquement les guillemets externes d'une chaîne
char *remove_quotes(char *str)
{
    int i, j;
    int len = strlen(str);
    char *result;
    char quote_type = 0;  // 0 = aucun, ' = simple, " = double
    
    if (!str)
        return (NULL);
    
    result = malloc(len + 1);
    if (!result)
        return (NULL);
    
    // Détecter si la chaîne commence par un guillemet
    if (len > 0 && (str[0] == '"' || str[0] == '\''))
        quote_type = str[0];
    
    i = 0;
    j = 0;
    
    // Si la chaîne commence par un guillemet, on l'ignore
    if (quote_type != 0)
        i++;
    
    // Copier le contenu en préservant tous les caractères internes
    while (i < len)
    {
        // Si on arrive au guillemet fermant correspondant à la fin, on l'ignore
        if (quote_type != 0 && str[i] == quote_type && i == len - 1)
            break;
            
        // Dans tous les autres cas, on copie le caractère
        result[j++] = str[i++];
    }
    result[j] = '\0';
    return (result);
}

