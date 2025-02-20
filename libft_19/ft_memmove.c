/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2024/10/21 19:11:12 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*memmove - Copie n octets de src vers dest, 
 * en gérant correctement le chevauchement des zones mémoire
 * Retourne un pointeur vers dest*/
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!src && !dest)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}
/*
#include <stdio.h>

int main(void)
{
	char dest[] = "oldstring";
	const char src[]  = "newstring";

	printf("Avant memmove dest = %s, src = %s\n", dest, src);
	ft_memmove(dest, src, 9);
	printf("Après memmove dest = %s, src = %s\n", dest, src);

	return 0;
}
*/
