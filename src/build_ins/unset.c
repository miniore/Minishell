/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:22:45 by miniore           #+#    #+#             */
/*   Updated: 2025/06/03 13:13:00 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_backpack *backpack)
{
	t_list *temp;
	t_env	*env_node;

	temp = backpack->commands_lst[0].arguments;
	env_node = search_node(&backpack->env, temp->content);
	if (!env_node)
		return ;
	erase_node(env_node);
}
