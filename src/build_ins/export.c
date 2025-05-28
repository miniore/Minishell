/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:04:42 by porellan          #+#    #+#             */
/*   Updated: 2025/05/28 19:48:46 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char    *ft_var_content(char *str)
{
    char    *content;
    int     i;
    size_t  len;

    i = 0;
    len = ft_strlen(str);
    while(str[i - 1] != 61)
        i++;
    if(!str[i])
        return(NULL);
    content = ft_substr(str, i, len);
    return (content);
}

void    ft_export(t_backpack *backpack)
{
    t_list  *actual;
    char    *var;
    char    *content;

    backpack->n = 0;
    actual = backpack->commands_lst[backpack->n].arguments;
    while(actual)
    {
        if(!ft_strchr(actual->content, 61))
        {
            actual = actual->next;
            continue ;
        }
        var = name_var(actual->content);
        if(!var || (!ft_isalpha(var[0]) && var[0] != '_'))
        {
            printf("Minichelita: export: `%s': not a valid identifier\n", (char *)actual->content);
            actual = actual->next;
            continue ;
        }
        content = ft_var_content(actual->content);
        env_add_last(&backpack->env, new_node(var, content));
        actual = actual->next;
    }
}
