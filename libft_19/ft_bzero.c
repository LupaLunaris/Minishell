/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2024/10/15 16:44:27 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ft_bzero - Remplit les premiers n octets 
 * de la zone mémoire pointée par s avec des zéros.
 * s: Pointeur vers la zone mémoire à remplir.
 * n: Nombre d'octets à remplir avec des zéros.
 */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}

/*
#include <stdio.h>
int main() {
	char str[] = "hello";
	ft_bzero(str,2);
	printf("%s/n", str);
return 0;
}
*/
