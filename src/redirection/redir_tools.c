/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:59:11 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/09 21:26:55 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_n_hdocs(t_redir *redirection)
{
    int i;

    i = 0;
    while(redirection)
    {
        printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
        if(ft_strcmp(redirection->op, "<<")  == 0)
            i++;
        redirection = redirection->next;
    }
    printf("||((%s En_Linea %d))||=> %i\n", __FILE__,__LINE__, i);
    return(i);
}