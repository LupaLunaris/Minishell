/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2024/10/21 18:43:12 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* memcmp - Compare les premiers n octets 
 * des blocs de mémoire pointés par s1 et s2
 * Retourne un entier inférieur, égal ou supérieur 
 * à zéro si les premiers n octets de s1 sont 
 * respectivement inférieurs, égaux ou supérieurs à ceux de s2*/
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n--)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}

/*
#include <stdio.h>

int main(){
	char str1[] = "hello";
	char str2[] = "";
	int result = ft_memcmp(str1, str2, 5);
	printf("%d\n", result);
	return 0;
}
*/
