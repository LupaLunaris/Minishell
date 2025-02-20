/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:52:36 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/15 16:58:58 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*isprint - Vérifie si un caractère 
 *est imprimable (valeurs 32 à 126 incluses)*/
#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/*
#include <stdio.h>

int main(void)
{
	int ch1 = ' ';
	int ch2 = 127;
	int ch3 = 'A';

	printf("%d\n", ft_isprint(ch1));
	printf("%d\n", ft_isprint(ch2));
	printf("%d\n", ft_isprint(ch3));

	return 0;
}
*/
