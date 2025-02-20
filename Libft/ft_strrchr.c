/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:27:53 by porellan          #+#    #+#             */
/*   Updated: 2023/10/14 10:32:52 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			*str;
	unsigned char	n;

	n = (unsigned char)c;
	str = (char *)s;
	i = 0;
	while (str[i] != '\0')
		i++;
	if (n == 0)
		return (&str[i]);
	while (i--)
	{
		if (str[i] == n)
			return (&str[i]);
	}
	return (0);
}
