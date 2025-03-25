/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:51:40 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/09 19:07:23 by jpaulis          ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

/* Applique la fonction f à chaque caractère d'une chaîne 
 * passée en paramètre s, en utilisant également l'index 
 * de chaque caractère dans la chaîne
 * s: La chaîne de caractères sur laquelle itérer.
 * f: La fonction à appliquer à chaque caractère
*/
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (s && f)
	{
		while (s[i] != '\0')
		{
			f(i, &s[i]);
			i++;
		}
	}
}
