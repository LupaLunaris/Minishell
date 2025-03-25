/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:49:41 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/15 16:55:49 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*isascii - Vérifie si un caractère est 
 * un caractère ASCII (valeurs 0 à 127)*/
#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*
#include <stdio.h>

int main()
{
	int ch1 = 65;
	int ch2 = 200;
	int ch3 = 127;

	printf("%d: %d\n", ch1, ft_isascii(ch1));
	printf("%d: %d\n", ch2, ft_isascii(ch2));
	printf("%d: %d\n", ch3, ft_isascii(ch3));

	return 0;
}
*/
