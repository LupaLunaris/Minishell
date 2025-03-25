/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:  2024/10/08 01:36:36 by jpaulis           #+#    #+#            */
/*   Updated: 2024/10/09 16:15:46 by jpaulis          ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

//strcmp - Compare deux chaînes de caractères str1 et str2
//Retourne un entier inférieur, égal ou supérieur à zéro si str1 est respectivement inférieure, égale ou supérieure à str2

#include "libft.h"

int ft_strcmp(const char *str1, const char *str2)
{
    int i;

    i = 0;
    while (str1[i] && str1[i] == str2[i])
        i++;
    return (str1[i] - str2[i]);
}

/*
#include <stdio.h>
#include <string.h>

int main() {
    const char *str1 = "abcd";
    const char *str2 = "abdc";
    int result = ft_strcmp(str1, str2);

    printf("%d", result);
    return 0;
}
*/
