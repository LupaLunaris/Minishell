/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:04:09 by Jpaulis           #+#    #+#             */
/*   Updated: 2024/10/22 15:22:30 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_lstnew - crée un nouveau maillon pour la liste chainée */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_elem;

	new_elem = (t_list *)malloc(sizeof(t_list));
	if (!new_elem)
		return (NULL);
	new_elem->content = content;
	new_elem->next = NULL;
	return (new_elem);
}

/*
#include <stdio.h>

int main ()
{
t_list *elem;

elem = ft_lstnew("hello world");
printf("%s\n", (char *)elem->content);
free (elem);
return 0;
}*/