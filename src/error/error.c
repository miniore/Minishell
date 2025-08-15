/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:02:07 by miniore           #+#    #+#             */
/*   Updated: 2025/08/15 20:05:15 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_syserr_exit(t_bp *bp, char *err)
{
	perror(err);
	bp->exit_status = errno;
	bp->commands_nb = 0;
	bp->err_flag = 1;
	exit(bp->exit_status);
}

void	ft_put_syserr(t_bp *bp, char *err)
{
	perror(err);
	bp->exit_status = errno;
	bp->commands_nb = 0;
	bp->err_flag = 1;
}

void	ft_put_pererr(t_bp *bp, char *err, int n)
{
	ft_putstr_fd(err, 2);
	bp->exit_status = n;
	bp->err_flag = 1;
}
