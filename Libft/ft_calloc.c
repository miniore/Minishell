/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:32:57 by porellan          #+#    #+#             */
/*   Updated: 2023/10/10 17:10:27 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elem_count, size_t elem_size)
{
	size_t	total_size;
	void	*memory_block;

	total_size = elem_count * elem_size;
	if (elem_count != '\0' && total_size / elem_count != elem_size)
		return (0);
	memory_block = malloc(total_size);
	if (!memory_block)
		return (0);
	if (memory_block != (void *)0)
		ft_memset(memory_block, 0, total_size);
	return (memory_block);
}
