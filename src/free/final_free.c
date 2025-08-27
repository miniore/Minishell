/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:46:18 by porellan          #+#    #+#             */
/*   Updated: 2025/08/27 12:34:44 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_free(t_bp *bp)
{
	if (!bp)
		return ;
	if (bp->commands_lst)
		free_command_list(bp->commands_lst, bp->commands_nb);
}

void	ft_exit_free(t_bp *bp)
{
	int	es;

	if (!bp)
		return ;
	if (bp->commands_lst)
		free_command_list(bp->commands_lst, bp->commands_nb);
	ft_free_env(bp->env);
	if(g_exit_status == 130)
		bp->exit_status = g_exit_status;
	es = bp->exit_status;
	free(bp);
	exit(es);
}

void	ft_final_free(t_bp *bp)
{
	if (!bp)
		return ;
	if (bp->commands_lst)
		free_command_list(bp->commands_lst, bp->commands_nb);
	ft_free_env(bp->env);
	free(bp);
}
