/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:12:40 by porellan          #+#    #+#             */
/*   Updated: 2024/11/14 10:55:51 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char	*new_str;
	size_t	new_str_len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	new_str_len = ft_strlen(s1) + ft_strlen(s2);
	new_str = ft_calloc(new_str_len + 1, 1);
	if (new_str == NULL)
		return (0);
	i = 0;
	j = 0;
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

char	*ft_strchr_gnl(const char *s, int n)
{
	int		i;
	char	c;
	char	*str;

	if (!s || !n)
		return (NULL);
	i = 0;
	c = (char)n;
	str = (char *)s;
	while (str && str[i] != '\0')
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	if (str[i] != c)
		return (NULL);
	return (&str[i]);
}
