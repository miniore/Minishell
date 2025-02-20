/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:20:00 by porellan          #+#    #+#             */
/*   Updated: 2025/01/22 14:50:31 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*backup;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		backup = (*lst)->next;
		del((*lst)->content);
		free((*lst));
		(*lst) = backup;
	}
	(*lst) = 0;
}
