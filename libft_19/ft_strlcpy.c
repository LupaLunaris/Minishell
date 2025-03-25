/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:56:32 by Jpaulis           #+#    #+#             */
/*   Updated: 2024/10/15 18:56:32 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Copie une chaine de caractères et
 * garantit que le buffer de dst est terminé par \0
 * retourne la longueur totale*/
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srcsize;
	size_t	i;

	srcsize = ft_strlen(src);
	if (size == 0)
		return (srcsize);
	if (srcsize >= size)
		i = size - 1;
	else
		i = srcsize;
	ft_memcpy(dst, src, i);
	dst[i] = '\0';
	return (srcsize);
}
