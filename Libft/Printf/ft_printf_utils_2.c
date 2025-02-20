/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:57:43 by porellan          #+#    #+#             */
/*   Updated: 2023/11/23 17:01:57 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_ptr(unsigned long n, const char *format, int *counter)
{
	unsigned int	num;

	if (n > 15)
	{
		ft_print_ptr(n / 16, format, counter);
		if (*counter == -1)
			return ;
	}
	if (n > 0)
	{
		num = n % 16;
		ft_print_chr(format[num], counter);
		if (*counter == -1)
			return ;
	}
	if (!n)
	{
		ft_print_chr('0', counter);
		if (*counter == -1)
			return ;
	}
}

void	ft_print_hexa(unsigned int n, const char *format, int *counter)
{
	unsigned int	num;

	if (n > 15)
	{
		ft_print_hexa(n / 16, format, counter);
		if (*counter == -1)
			return ;
	}
	if (n > 0)
	{
		num = n % 16;
		ft_print_chr(format[num], counter);
		if (*counter == -1)
			return ;
	}
	if (!n)
	{
		ft_print_chr('0', counter);
		if (*counter == -1)
			return ;
	}
}
