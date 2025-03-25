/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:16:38 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/21 19:08:31 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*ft_strsub - Alloue (avec malloc) un tronçon 
 * de la chaîne de caractères passée en paramètres.
 *Retourne la copie "fraîche" du tronçon de la chaîne.
 */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		new_str[i] = s[start];
		start++;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/*
#include <stdio.h>
#include <stdlib.h>

int main() {
	char *s = "Hello World";
	unsigned int start = 5;
	size_t len = 4;

	char *new_str = ft_strsub(s, start, len);
	printf ("%s\n", new_str);
	free(new_str);
	return 0;
}
*/
