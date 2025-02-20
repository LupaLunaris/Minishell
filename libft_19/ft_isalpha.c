/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:56:15 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/15 16:53:35 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*isalpha - Vérifie si un caractère est une lettre de l'alphabet
 *Retourne 1 si le caractère est un lettre de l'alphabet sinon 0*/
#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

/*
#include <stdio.h>

int main()
{
    char ch1 = 'A';
    char ch2 = '1';
    char ch3 = 'z';

    printf("%d\n", ft_isalpha(ch1));
    printf("%d\n", ft_isalpha(ch2));
    printf("%d\n", ft_isalpha(ch3));

    return 0;
}
*/
