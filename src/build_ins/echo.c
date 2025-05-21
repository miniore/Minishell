/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:22:22 by frlorenz          #+#    #+#             */
/*   Updated: 2025/05/21 17:22:26 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_check_flag(char *flag)
{
    int i;

    i = 1;
    if(flag[i] == '\0')
        return(1);
    while(flag[i])
    {
        if(flag[i] != 110)
            return(1);
        i++;
    }
    return(0);
}

void    ft_echo(t_list *arg)
{
    t_list  *temp;
    bool    opt;
    int     flag;

    temp = arg;
    opt = false;
    flag = 0;
    while (temp->next)
    {
        if (((char*)temp->content)[0] == 45 && flag == 0)
        {
            if (!ft_check_flag((char*)temp->content))
            {
                opt = true;
                temp = temp->next;
                continue;
            }
        }
        printf("%s ", (char*)temp->content);
        flag = 1;
        temp = temp->next;
    }
    printf("%s", (char*)temp->content);
    if (opt == false)
        printf("\n");
}
