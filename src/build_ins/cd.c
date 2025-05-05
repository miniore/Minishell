/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:44 by frlorenz          #+#    #+#             */
/*   Updated: 2025/05/05 12:58:41 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd(t_list *arg)
{
    if(!arg)
    {
        if (chdir(getenv("HOME")) == -1)
           perror("cd");
    }
    else if(ft_lstsize(arg) == 1)
    {
        if (chdir((char *)arg->content) == -1)
           perror("cd");
    }
    else
        perror("cd: too many arguments");
        
}