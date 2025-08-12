/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:39:22 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/12 13:03:12 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_ctrl_c(int sig)
{
    (void)sig;
    g_exit_status = SIGINT; // SIGINT => 128 + 2
    write(1,"\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
void hdoc_ctrl_c(int sig)
{
    (void)sig;
    g_exit_status = SIGINT; // SIGINT => 128 + 2
    write(1,"\n", 1);
    rl_on_new_line();
    exit(130);
}