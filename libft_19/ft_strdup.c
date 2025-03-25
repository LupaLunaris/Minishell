/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2024/10/20 16:02:42 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* strdup - Duplique la chaîne de caractères s 
 * en allouant suffisamment de mémoire pour une copie 
 * et retourne un pointeur vers cette copie*/
#include "libft.h"

char	*ft_strdup(char *s)
{
	char	*s_copy;
	int		length;

	length = ft_strlen(s) + 1;
	s_copy = (char *)malloc(length);
	if (s_copy == NULL)
		return (NULL);
	ft_strlcpy(s_copy, s, length);
	return (s_copy);
}

/*
#include <stdio.h>

int main(void)
{
	char src[] = "Hello, world!";
	char *dst;

	dst = ft_strdup(src);
	printf("Dst: %s\n", dst);
	free(dst);

	return 0;
}
*/
