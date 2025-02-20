/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:55:34 by porellan          #+#    #+#             */
/*   Updated: 2023/10/16 18:26:31 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t s)
{
	size_t	i;
	int		j;

	if (!haystack && s == 0)
		return (0);
	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < s)
	{
		j = 0;
		while ((haystack[i] == needle[j] && needle[j] != '\0') && (i < s))
		{
			i++;
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)&haystack[i - j]);
		i = i - j + 1;
	}
	return (0);
}
