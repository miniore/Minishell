/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:39:57 by porellan          #+#    #+#             */
/*   Updated: 2024/06/20 13:44:28 by porellan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list *newNode;
	
	newNode = ft_lstnew(new);
	newNode -> next = *lst;
	*lst = newNode;
}
