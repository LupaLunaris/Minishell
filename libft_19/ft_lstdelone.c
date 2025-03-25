/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:46:26 by Jpaulis           #+#    #+#             */
/*   Updated: 2024/10/22 15:54:42 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Liberer la mémoire d'un maillon sans toucher aux autres */
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
