/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:59:11 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/11 15:21:34 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_n_hdocs(t_redir *redirection)
{
    int i;

    i = 0;
    while(redirection)
    {
        if(ft_strcmp(redirection->op, "<<")  == 0)
            i++;
        redirection = redirection->next;
    }
    return(i);
}