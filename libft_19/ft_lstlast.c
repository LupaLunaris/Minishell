/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:29:06 by Jpaulis           #+#    #+#             */
/*   Updated: 2024/10/22 15:33:29 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Retroune le dernier maillonn de la liste chainée */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
