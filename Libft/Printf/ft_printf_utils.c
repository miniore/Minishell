/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:57:43 by porellan          #+#    #+#             */
/*   Updated: 2024/05/13 14:30:15 by porellan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_printf.h"

void	ft_print_chr(char c, int *return_value)
{
	if (write(1, &c, 1) == -1)
		*return_value = -1;
	else
		(*return_value)++;
}

void	ft_print_str(char *str, int *counter)
{
	int	size;

	size = 0;
	if (!str)
		str = "(null)";
	while (str[size] != '\0')
	{
		ft_print_chr(str[size], counter);
		if (*counter == -1)
			return ;
		size++;
	}
}

void	ft_print_int(int n, int *counter)
{
	char	num;
	long	nb;

	nb = (long)n;
	if (nb < 0)
	{
		ft_print_chr('-', counter);
		if (*counter == -1)
			return ;
		nb *= (-1);
	}
	if (nb > 9)
	{
		ft_print_int((nb / 10), counter);
		if (*counter == -1)
			return ;
	}
	num = nb % 10 + '0';
	ft_print_chr(num, counter);
	if (*counter == -1)
		return ;
}

void	ft_print_uint(unsigned int n, int *counter)
{
	char	num;
	long	nb;

	nb = (long)n;
	if (nb > 9)
	{
		ft_print_uint((nb / 10), counter);
		if (*counter == -1)
			return ;
	}
	num = nb % 10 + '0';
	ft_print_chr(num, counter);
	if (*counter == -1)
		return ;
}
