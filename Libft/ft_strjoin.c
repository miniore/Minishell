/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:51:40 by porellan          #+#    #+#             */
/*   Updated: 2023/10/16 18:37:52 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	new_str_len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	new_str_len = ft_strlen(s1) + ft_strlen(s2);
	new_str = ft_calloc(new_str_len + 1, 1);
	i = 0;
	j = 0;
	if (new_str == NULL)
		return (0);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	return (new_str);
}
