/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:22:45 by miniore           #+#    #+#             */
/*   Updated: 2025/08/15 20:53:23 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_bp *bp)
{
	t_list	*temp;
	t_env	*env_node;

	temp = bp->commands_lst[0].arguments;
	if (!temp)
		return ;
	while (temp)
	{
		env_node = search_node(&bp->env, temp->content);
		if (!env_node)
			temp = temp->next;
		else
		{
			erase_node(&bp->env, env_node);
			temp = temp->next;
		}
	}
}
