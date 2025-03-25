/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:14:41 by Jpaulis           #+#    #+#             */
/*   Updated: 2024/10/23 13:41:52 by jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* va itérer sur chaque maillon de la liste,
 * appliquer une fonction f au contenu de chaque maillon 
 * et créer une nouvelle liste avec les résultats 
 * de ces applications */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;
	void	*new_content;

	if (!f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_elem = ft_lstnew(new_content);
		if (!new_elem)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_elem);
		lst = lst->next;
	}
	return (new_list);
}

/*
int main(void)
{
	t_list *head = ft_lstnew("First");
	t_list *new_list;

	new_list = ft_lstmap(head, ft_strdup, free);

	printf("%s\n", (char *)new_list->content);

	ft_lstclear(&new_list, free);
	ft_lstclear(&head, free);

	return 0;
}
*/
