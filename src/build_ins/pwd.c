/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:17:56 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/15 20:52:16 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_bp *bp)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_put_syserr(bp, "Minichelita");
		return ;
	}
	printf("%s\n", path);
	free(path);
}
