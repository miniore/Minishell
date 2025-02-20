/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:48:46 by porellan          #+#    #+#             */
/*   Updated: 2023/10/16 18:40:04 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	int		x;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		x = s[i];
		write(fd, &x, 1);
		i++;
	}
	write(fd, "\n", 1);
}
