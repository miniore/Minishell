/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:41:42 by porellan          #+#    #+#             */
/*   Updated: 2023/10/10 17:20:35 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*actual;

	actual = lst;
	while (actual != 0)
	{
		if (actual -> next == NULL)
			return (actual);
		actual = actual -> next;
	}
	return (actual);
}
