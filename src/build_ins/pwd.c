/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:17:56 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/15 20:19:25 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_backpack *backpack)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_put_syserr(backpack, "Minichelita");
		return ;
	}
	printf("%s\n", path);
	free(path);
}
