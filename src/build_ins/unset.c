/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:22:45 by miniore           #+#    #+#             */
/*   Updated: 2025/07/29 16:45:17 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_backpack *backpack)
{
	t_list *temp;
	t_env	*env_node;

	temp = backpack->commands_lst[0].arguments;
	if (!temp)
		return;
	while(temp)
	{
		env_node = search_node(&backpack->env, temp->content);
		if (!env_node)
			temp=temp->next;
		else
		{
			erase_node(&backpack->env, env_node);
			temp=temp->next;
		}
	}
}
