/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:43:16 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/15 16:56:44 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*isdigit - Vérifie si un caractère est un chiffre (0-9)
 * Retourne 1 si le caractère est un chiffre, 0 sinon*/
#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*
#include <stdio.h>

int main()
{
    char ch1 = '5';
    char ch2 = 'A';
    char ch3 = '0';

    printf("%d\n", ft_isdigit(ch1));
    printf("%d\n", ft_isdigit(ch2));
    printf("%d\n", ft_isdigit(ch3));

    return 0;
}
*/
