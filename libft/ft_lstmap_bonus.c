/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:55:55 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/20 10:58:33 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*def;
	t_list	*auxdef;

	if (!lst)
		return (0);
	def = malloc(sizeof(t_list));
	if (!def)
		return (0);
	auxdef = def;
	while (lst)
	{
		auxdef->content = f(lst->content);
		lst = lst->next;
		if (lst)
		{
			auxdef->next = malloc(sizeof(t_list));
			if (!auxdef->next)
				ft_lstclear(&def, del);
			auxdef = auxdef->next;
		}
		else
			auxdef->next = 0;
	}
	return (def);
}
