/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:53:15 by porellan          #+#    #+#             */
/*   Updated: 2023/10/14 13:28:44 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*destino;
	const char	*origen;
	size_t		i;

	destino = (char *)dest;
	origen = (const char *)src;
	i = 0;
	if (dest == NULL && src == NULL)
		return (dest);
	while (i < n)
	{
		destino[i] = origen[i];
		i++;
	}
	return (dest);
}
