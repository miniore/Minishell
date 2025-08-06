/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:02:07 by miniore           #+#    #+#             */
/*   Updated: 2025/08/06 21:02:32 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_put_syserr_exit(t_backpack *backpack, char *err)
{
    perror(err);
    g_exit_status = errno;
    backpack->commands_nb = 0;
    backpack->err_flag = 1;
    exit(g_exit_status);
}

void    ft_put_syserr(t_backpack *backpack, char *err)
{
    perror(err);
    g_exit_status = errno;
    backpack->commands_nb = 0;
    backpack->err_flag = 1;
}

void    ft_put_pererr(t_backpack *backpack, char *err, int n)
{
    ft_putstr_fd(err, 2);
    g_exit_status = n;
    backpack->commands_nb = 0;
    backpack->err_flag = 1;
}
