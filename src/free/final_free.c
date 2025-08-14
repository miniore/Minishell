/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:46:18 by porellan          #+#    #+#             */
/*   Updated: 2025/08/13 20:47:36 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_free(t_backpack *backpack)
{
    if (!backpack)
        return;
    if(backpack->commands_lst)
        free_command_list(backpack->commands_lst, backpack->commands_nb);
}

void	ft_exit_free(t_backpack *backpack)
{
    if (!backpack)
        return;
    if(backpack->commands_lst)
        free_command_list(backpack->commands_lst, backpack->commands_nb);
    ft_free_env(backpack->env);
    free(backpack);
}
