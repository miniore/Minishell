/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:57:43 by porellan          #+#    #+#             */
/*   Updated: 2023/12/05 17:46:38 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

int			ft_printf(char const *ent, ...);
void		ft_print_chr(char c, int *counter);
void		ft_print_str(char *str, int *counter);
void		ft_print_int(int n, int *counter);
void		ft_print_uint(unsigned int n, int *counter);
void		ft_print_ptr(unsigned long n, const char *format, int *counter);
void		ft_print_hexa(unsigned int n, const char *format, int *counter);

#endif