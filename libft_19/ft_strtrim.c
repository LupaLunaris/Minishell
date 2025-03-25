/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:40:00 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/21 19:05:31 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*ft_strtrim - Alloue de la mémoire avec malloc 
 * à une copie de la chaîne
 * Retourne une chaine de caractère "fraîche" 
 * trimmée ou une copie de s sinon
 * s1 : la chaîne de caractère a trimmer
 * set : Le set de référence de caractères a trimmer
 */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	size_t	end;
	size_t	start;

	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	new_str = (char *)malloc((end - start + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, &s1[start], end - start + 1);
	return (new_str);
}

/*
#include <stdio.h>
#include <stdlib.h>
int main()
{
	char test_str[] = "   Bonjour tout le monde   ";
	char *result = ft_strtrim(test_str);

	printf("Résultat: '%s'\n", result);
	free(result);
	return 0;
}
*/
