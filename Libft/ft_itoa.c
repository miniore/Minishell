/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:27:13 by porellan          #+#    #+#             */
/*   Updated: 2023/10/10 17:16:56 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	counter(long n)
{
	long	size;

	size = 0;
	if (n == 0)
		size++;
	if (n < 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*num;
	long	t;

	t = (long)n;
	i = counter(n);
	num = (char *)ft_calloc(i + 1, 1);
	if (!num)
		return (0);
	if (t == 0)
		num[0] = 0;
	if (t < 0)
	{
		t *= -1;
		num[0] = '-';
	}
	while (i > 0 && num[--i] != '-')
	{
		num[i] = (t % 10) + '0';
		t = t / 10;
	}
	return (num);
}
