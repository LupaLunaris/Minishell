/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2024/10/21 19:09:14 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * strlcat - Concatène src à la fin de dst, 
 * en veillant à éviter tout dépassement de tampon.
 *
 * dst: Pointeur vers la destination (chaîne de caractères)
 * src: Pointeur vers la source (chaîne de caractères à ajouter)
 * size: Taille totale du buffer de destination
 *
 * Retourne la taille totale de la chaîne qu'elle a essayé de créer.
 */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (size <= dst_len)
		return (size + src_len);
	i = 0;
	while (src[i] && (dst_len + i) < (size - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/*
#include <stdio.h>

int main()
{
	char dst[20] = "Hello";
	char src[] = ", world!";
	
	int result = ft_strlcat(dst, src, sizeof(dst));

	printf("Dst: %s\n", dst);
	printf("Total Length: %d\n", result);

	return 0;
}
*/
