/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:04:42 by porellan          #+#    #+#             */
/*   Updated: 2025/08/04 20:15:50 by miniore          ###   ########.fr       */
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
    while(str[i] != '=')
        i++;
    if(!str[i])
        return(NULL);
    i++;
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
    if(!backpack->commands_lst[backpack->n].arguments)
        ft_env(backpack, 0);
    while(actual)
    {
        if(!ft_strchr(actual->content, '='))
        {
            actual = actual->next;
            continue ;
        }
        var = name_var(actual->content);
        if(!var || (!ft_isalpha(var[0]) && var[0] != '_'))
        {
            ft_put_pererr(backpack, "Minichelita: export: `%s': not a valid identifier.\n", 258);
            actual = actual->next;
            continue ;
        }
        content = ft_var_content(actual->content);
        if (!content)
            content = "";
        if (!search_node(&backpack->env, var))
            env_add_last(&backpack->env, new_node(var, content));
        else
            modify_node(search_node(&backpack->env, var), NULL, content);
        free(var);
        actual = actual->next;
    }
    
}
