/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:46:40 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/15 16:48:23 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*isalnum - Vérifie si un caractère est une lettre 
 *(a-z, A-Z) ou un chiffre (0-9)*/
#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/*
#include <stdio.h>

int main(void)
{
	char ch1 = 'A';
	char ch2 = '1';
	char ch3 = '%';

	printf("%d\n", ft_isalnum(ch1));
	printf("%d\n", ft_isalnum(ch2));
	printf("%d\n", ft_isalnum(ch3));

	return 0;
}
*/
