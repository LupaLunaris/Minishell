/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:54:27 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/15 18:51:25 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* toupper - Convertit une lettre minuscule en majuscule
 * Retourne le caractère converti en majuscule, 
 * ou le caractère inchangé s'il n'est pas une lettre minuscule
 */
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	return (c);
}

/*
#include <stdio.h>

int main(void)
{
	char ch1 = 'a';
	char ch2 = 'A';
	char ch3 = '1';

	printf("%c: %c\n", ch1, ft_toupper(ch1));
	printf("%c: %c\n", ch2, ft_toupper(ch2));
	printf("%c: %c\n", ch3, ft_toupper(ch3));

	return 0;
}
*/
