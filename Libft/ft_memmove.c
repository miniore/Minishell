/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:42:02 by porellan          #+#    #+#             */
/*   Updated: 2023/10/14 13:27:46 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*origen;
	char	*destino;
	size_t	i;

	destino = (char *)dest;
	origen = (char *)src;
	if (dest == NULL && src == NULL)
		return (dest);
	if (src < dest)
	{
		i = n;
		while (i > 0)
		{
			destino[i - 1] = origen[i - 1];
			i--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
