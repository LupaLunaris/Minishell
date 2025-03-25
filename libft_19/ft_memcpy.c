/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2024/10/21 19:07:50 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*memcpy - Copie n octets de la zone 
 *mémoire src vers la zone mémoire dest*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	if (!dest && !src)
		return (NULL);
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (n--)
		*d++ = *s++;
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char src[] = "Hello, world!";
	char dest[50];

	memcpy(dest, src, 4);
	dest[4] = '\0';

	printf("Dest: %s\n", dest);

	return 0;
}
*/
