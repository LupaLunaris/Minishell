/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:32:16 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/21 18:44:30 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_strjoin - Alloue avec malloc et concaténate s1 et s2.
 * Retourne une chaîne de caractère "fraiche" 
 * terminée par '\0' résultant de la concanétation.
 */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = (char *)malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, len1 + 1);
	ft_strlcpy(new_str + len1, s2, len2 + 1);
	return (new_str);
}

/*
#include <stdio.h>
#include <stdlib.h>

int main() {
	char *s1 = "Hello,";
	char *s2 = "World!";
	char *new_str = ft_strjoin(s1, s2);
	printf("%s\n", new_str);
	free(new_str);
	return 0;
}
*/
