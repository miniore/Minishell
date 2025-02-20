/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:18:28 by porellan          #+#    #+#             */
/*   Updated: 2024/10/10 19:07:00 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*actual;
	int		i;

	actual = lst;
	i = 0;
	while (actual != 0)
	{
		actual = actual -> next;
		i++;
	}
	return (i);
}
