/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:13:13 by porellan          #+#    #+#             */
/*   Updated: 2025/08/15 17:04:11 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_exit(t_backpack *backpack)
{
    g_exit_status = backpack->exit_status;
    ft_final_free(backpack);
    printf("Nos vamos. Saliendo.\n");
    exit(g_exit_status);
}
