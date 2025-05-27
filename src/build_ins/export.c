/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:04:42 by porellan          #+#    #+#             */
/*   Updated: 2025/05/27 19:53:13 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void    ft_export(t_backpack *backpack)
{
    t_list  *actual;
    char *var;
    char    *content;
    char    *content;

    backpack->n = 0;
    actual = backpack->commands_lst[backpack->n].arguments;
    while(actual->next)
    {
        if(!ft_strchr(actual->content, 61))
        {
            actual = actual->next;
            break ;
        }
        var = name_var(actual->content);
        content = //funcion que saque el content
        env_add_last(env, new_node(var, content));
        actual = actual->next;
    }
}
