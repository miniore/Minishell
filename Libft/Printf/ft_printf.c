/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:57:43 by porellan          #+#    #+#             */
/*   Updated: 2024/01/08 20:57:37 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_symbol(va_list args, char conv, int *ptr_len)
{
	if (conv == 'c')
		ft_print_chr(va_arg(args, int), ptr_len);
	if (conv == 's')
		ft_print_str(va_arg(args, char *), ptr_len);
	if (conv == 'p')
	{
		ft_print_chr('0', ptr_len);
		if (*ptr_len == -1)
			return ;
		ft_print_chr('x', ptr_len);
		if (*ptr_len == -1)
			return ;
		ft_print_ptr(va_arg(args, unsigned long), "0123456789abcdef", ptr_len);
	}
	if (conv == 'd' || conv == 'i')
		ft_print_int(va_arg(args, int), ptr_len);
	if (conv == 'u')
		ft_print_uint(va_arg(args, unsigned int), ptr_len);
	if (conv == 'x')
		ft_print_hexa(va_arg(args, unsigned int), "0123456789abcdef", ptr_len);
	if (conv == 'X')
		ft_print_hexa(va_arg(args, unsigned int), "0123456789ABCDEF", ptr_len);
	else if (conv == '%')
		ft_print_chr('%', ptr_len);
}

int	ft_printf(char const *ent, ...)
{
	va_list	args;
	int		len;
	int		i;

	va_start(args, ent);
	len = 0;
	i = 0;
	while (ent[i++] != '\0')
	{
		if (ent[i - 1] == '%')
		{
			ft_symbol(args, ent[i], &len);
			i++;
		}
		else
			ft_print_chr(ent[i - 1], &len);
		if (len == -1)
			return (len);
	}
	va_end(args);
	return (len);
}
