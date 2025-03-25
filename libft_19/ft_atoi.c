/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2024/10/15 19:43:27 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* atoi convertit une chaîne de caractères en un entier.*/

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str > 8 && *str < 14))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
/* 
#include <stdio.h>

int ft_atoi(const char *str);

int main(void) {
	const char *str1 = "42";
	const char *str2 = "  -42";
	const char *str3 = "4193 hello";
	const char *str4 = "Hello word 123";
	const char *str5 = "-+91283472332";

	printf("ft_atoi(\"%s\") = %d\n", str1, ft_atoi(str1));
	printf("ft_atoi(\"%s\") = %d\n", str2, ft_atoi(str2));
	printf("ft_atoi(\"%s\") = %d\n", str3, ft_atoi(str3));
	printf("ft_atoi(\"%s\") = %d\n", str4, ft_atoi(str4));
	printf("ft_atoi(\"%s\") = %d\n", str5, ft_atoi(str5));

	return 0;
}
*/
