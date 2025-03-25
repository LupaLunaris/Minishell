/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2025/02/20 14:59:07 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_strlen - Calcule la longueur 
 * de la chaîne de caractères c 
 * (ne compte pas le caractère nul '\0')
 * Retourne la longueur de la chaîne de caractères
 */
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/*
#include <stdio.h>

int main(void)
{
	char str[] = "Hello, world!";
	int len = ft_strlen(str);

	printf("Length: %d\n", len);

	return 0;
}
*/
