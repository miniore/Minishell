/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:09:32 by porellan          #+#    #+#             */
/*   Updated: 2023/10/16 16:41:57 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*result;

	result = 0;
	if (!lst || !f)
		return (0);
	while (lst)
	{
		temp = ft_lstnew(lst->content);
		if (!temp)
		{
			ft_lstclear(&result, del);
			return (0);
		}
		temp -> content = f(temp -> content);
		ft_lstadd_back(&result, temp);
		lst = lst->next;
	}
	return (result);
}
