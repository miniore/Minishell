/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:43:57 by porellan          #+#    #+#             */
/*   Updated: 2024/05/16 13:01:56 by porellan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

static int	str_numb(const char *s, char c)
{
	int	strings;
	int	i;

	strings = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i])
		strings++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			strings++;
		i++;
	}
	return (strings);
}

static size_t	str_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

static char	**free_split(char **s, int max_size)
{
	while (max_size >= 0)
		free(s[max_size--]);
	free(s);
	return (0);
}

static char	**array_maker(char const *s, char **array, int n, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (n--)
	{
		while (s[i] == c && s[i])
			i++;
		array[j] = ft_substr(s, i, str_len(s + i, c));
		if (!array[j])
			return (free_split(array, j));
		while (s[i] != c && s[i])
			i++;
		j++;
	}
	array[j] = 0;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		strings;
	char	**array;

	if (!s)
		return (NULL);
	strings = str_numb(s, c);
	array = (char **)malloc((strings + 1) * sizeof(char *));
	if (!array)
		return (0);
	array = array_maker(s, array, strings, c);
	return (array);
}
