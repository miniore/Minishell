/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:01:43 by porellan          #+#    #+#             */
/*   Updated: 2023/10/11 16:40:21 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t s)
{
	size_t	i;
	size_t	size_src;

	size_src = 0;
	i = 0;
	while (src[size_src] != '\0')
		size_src++;
	while ((src[i] != '\0' && i < s - 1) && s != 0)
	{
		dest[i] = src[i];
		i++;
	}
	if (s > 0)
		dest[i] = '\0';
	return (size_src);
}
