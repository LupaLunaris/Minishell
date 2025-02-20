/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2024/10/15 17:29:55 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Cette fonction remplit les n premiers octets 
 *de la zone mémoire pointée par str avec la valeur c*/

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (n > 0)
	{
		*ptr = (unsigned char)c;
		ptr++;
		n--;
	}
	return (str);
}

/*
#include <stdio.h>
#include <string.h>
int main() {
	char str[50] = "Hello, World!";
	printf("%s\n", str);
	ft_memset(str + 7, '*', 5);
	printf("%s\n", str);

	return 0;
}
*/
