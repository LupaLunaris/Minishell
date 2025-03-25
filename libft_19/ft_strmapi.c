/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:26:56 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/10 11:01:15 by jpaulis          ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

/* Applique la fonction f à chaque caractère 
 * de la chaîne s en passant l'index du caractère et 
 * crée une nouvelle chaîne résultant de cette transformation.
 * Retourne une copie "fraîche" de la chaîne modifiée.
 * s: La chaîne de caractères sur laquelle itérer.
 * f: La fonction à appliquer à chaque caractère.
 */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	new_str = (char *)malloc(ft_strlen(s)+1);
	if (!new_str)
		return (NULL);
	while (s[i])
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/*
#include <stdio.h>
#include <stdlib.h>

char ft_toupper_mapi(unsigned int index, char c)
{
	(void)index;
	return (ft_toupper(c));
}

int main()
{
	char *str = "bonjour";
	char *new_str = ft_strmapi(str, ft_toupper_mapi);

	printf("Original : %s\n", str);
	printf("Modifié : %s\n", new_str);
	free(new_str);

	return 0;
}
*/
