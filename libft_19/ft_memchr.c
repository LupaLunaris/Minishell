/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2024/10/15 17:12:22 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*memchr - Cherche la première occurrence 
 *du caractère ch dans les premiers n octets
 *de la zone mémoire pointée par ptr.*/
#include "libft.h"

void	*ft_memchr(const void *ptr, int ch, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (n > 0)
	{
		if (*p == (unsigned char)ch)
			return (p);
		p++;
		n--;
	}
	return (NULL);
}

/*
#include <stdio.h>

void *ft_memchr(const void *ptr, int ch, size_t n);

int main(void)
{
	const char str[] = "Hello, world!";
	char *result;

	result = ft_memchr(str, 'o', 12);
	if (result)
		printf("Trouvé à la position : %ld\n", result - str);
	else
		printf("Non trouvé\n");

	return 0;
}
*/
