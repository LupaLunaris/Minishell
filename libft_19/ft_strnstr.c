/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2024/10/23 13:02:37 by jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* strnstr - Cherche la première occurrence 
 * de la chaîne needle dans les premiers len caractères de la chaîne haystack
 * Retourne un pointeur vers le début de la chaîne trouvée, 
 * ou NULL si needle n'est pas trouvée dans 
 * les premiers len caractères de haystack
 */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *) haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j] && (i + j) < len)
		{
			j++;
			if (needle[j] == '\0')
				return ((char *) haystack + i);
		}
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int main(){
	const char *haystack = "Hello world";
	const char *needle = "world";
	size_t len = 10;
	char *result = ft_strnstr(haystack, needle, len);

		printf("%s\n", result);
	return 0;
}
*/
