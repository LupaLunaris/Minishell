/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2024/10/22 16:44:38 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*strchr - Cherche la première occurrence 
 *du caractère c dans la chaîne de caractères str*/
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	uc;

	if (str == NULL)
		*(char *)str = '\0';
	uc = (unsigned char)c;
	if (!str)
		return (NULL);
	while (*str)
	{
		if ((unsigned char)*str == uc)
			return ((char *)str);
		str++;
	}
	if (uc == '\0')
		return ((char *)str);
	return (NULL);
}

/* 
#include <stdio.h>

int main(void)
{
	const char str[] = "Hello, world!";
	char *result;

	result = ft_strchr(str, 'o');
	if (result)
		printf("Caractère trouvé à la position : %ld\n", result - str);
	else
		printf("Caractère non trouvé\n");

	return 0;
}
*/
