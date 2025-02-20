/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:31:25 by porellan          #+#    #+#             */
/*   Updated: 2023/10/11 16:23:26 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substring;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		substring = (char *)ft_calloc(i + 1, 1);
		if (!substring)
			return (0);
		return (substring);
	}
	while (i < len && s[i + start] != '\0')
		i++;
	substring = (char *)ft_calloc(i + 1, 1);
	if (!substring)
		return (0);
	i = 0;
	while (i < len && s[i + start] != '\0')
	{
		substring[i] = s[i + start];
		i++;
	}
	return (substring);
}
