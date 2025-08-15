/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:13:13 by porellan          #+#    #+#             */
/*   Updated: 2025/08/15 20:14:58 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_bp *bp)
{
	g_exit_status = bp->exit_status;
	ft_final_free(bp);
	printf("Nos vamos. Saliendo.\n");
	exit(g_exit_status);
}
