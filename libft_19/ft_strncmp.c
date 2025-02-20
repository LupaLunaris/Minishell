/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2024/10/21 18:50:38 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* strncmp - Compare jusqu'à n caractères 
 * des chaînes de caractères str1 et str2
 * Retourne un entier inférieur, égal ou supérieur 
 * à zéro si str1 est respectivement inférieure, 
 * égale ou supérieure à str2
 */
#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	if (n == 0)
		return (0);
	while (*str1 && (*str1 == *str2) && n > 1)
	{
		n--;
		str1++;
		str2++;
	}
	return ((unsigned char)*str1 - (unsigned char)*str2);
}

/*
#include <stdio.h>

int main() {
	char str1[]= "Hello";
	char str2[]= "Helli";
	size_t n = 0;
	int result = ft_strncmp(str1, str2, n);

	printf("%d\n", result);
	return 0;
}
*/
