/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:32:20 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/20 17:43:01 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*ft_itoa - Convertit un entier en une chaine de caractères
 * retourne la chaine de caractère
 */
#include "libft.h"

static int	ft_len_num(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;

	num = (long)n;
	len = ft_len_num(num);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memset(str, 0, len + 1);
	str[len] = '\0';
	len--;
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (len >= 0 && str[len] != '-')
	{
		str[len] = num % 10 + '0';
		num /= 10;
		len--;
	}
	return (str);
}
