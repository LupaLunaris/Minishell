/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:10:55 by Jpaulis           #+#    #+#             */
/*   Updated: 2024/10/22 16:14:10 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* itère sur la list lst et applique 
 * la fonction f au contenu de chaque element */
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
