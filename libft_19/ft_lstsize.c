/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:23:13 by Jpaulis           #+#    #+#             */
/*   Updated: 2024/10/22 15:28:43 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Compte et retourne le nombre de maillons de la liste*/
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
