/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:00:31 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/15 18:50:11 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* tolower - Convertit une lettre majuscule en minuscule
 * Retourne le caractère converti en minuscule, 
 * ou le caractère inchangé s'il n'est pas une lettre majuscule
 */
#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}

/*
#include <stdio.h>

int main(void)
{
	char ch1 = 'A';
	char ch2 = 'a';
	char ch3 = '1';

	printf("%c: %c\n", ch1, ft_tolower(ch1));
	printf("%c: %c\n", ch2, ft_tolower(ch2));
	printf("%c: %c\n", ch3, ft_tolower(ch3));

	return 0;
}
*/
