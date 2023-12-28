/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:32:51 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/28 19:39:47 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*curr;
	t_list	*new;
	t_list	*first;

	if (!lst)
		return (NULL);
	curr = lst;
	new = ft_lstnew(f(curr->content));
	if (!new)
		return (NULL);
	first = new;
	while (curr->next)
	{
		curr = curr->next;
		new->next = ft_lstnew(f(curr->content));
		if (!new->next)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		new = new->next;
	}
	return (first);
}
