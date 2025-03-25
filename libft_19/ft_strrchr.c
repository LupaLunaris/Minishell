/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2024/10/22 16:52:11 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*strrchr - Cherche la dernière occurrence 
 * du caractère c dans la chaîne de caractères str*/
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char			*last_occurrence;
	unsigned char	uc;

	if (str == NULL)
		*(char *)str = '\0';
	last_occurrence = NULL;
	uc = (unsigned char)c;
	if (!str)
		return (NULL);
	while (*str)
	{
		if ((unsigned char)*str == uc)
			last_occurrence = (char *)str;
		str++;
	}
	if (uc == '\0')
		return ((char *)str);
	return (last_occurrence);
}

/*
#include <stdio.h>

int main() {
	const char *str = "Bonjour tout le monde";
	char ch = 'o';
	char *result = ft_strrchr(str, ch);

	printf("%td\n", result - str);
	return 0;
}
*/
