/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:51:52 by porellan          #+#    #+#             */
/*   Updated: 2023/10/14 13:02:55 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		i;
	char		*duplicated;
	size_t		str_size;

	i = 0;
	str_size = ft_strlen(s1);
	duplicated = malloc(str_size + 1);
	if (duplicated == NULL)
		return (0);
	if (duplicated != NULL)
	{
		while (i < str_size)
		{
			duplicated[i] = s1[i];
			i++;
		}
	}
	duplicated[str_size] = '\0';
	return (duplicated);
}
