/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:27:59 by miniore           #+#    #+#             */
/*   Updated: 2025/05/26 19:41:49 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  ft_save_qarg(t_backpack *backpack, char *command, int i)
{
    //t_list *actual;
    t_list  *temp;
    char    *token;

    i++;
    //actual = backpack->commands_lst[backpack->n].arguments;
    ft_extract_content(backpack, command);
    token = ft_substr(command, i, backpack->len - i);
    temp = ft_lstnew(token);
    ft_lstadd_back(&backpack->commands_lst[backpack->n].arguments, temp);
    backpack->len++;
    //free(token);
}

void    ft_save_arg(t_backpack *backpack, char *command, int i)
{
    //t_list *actual;
    t_list  *temp;
    char    *token;

    //actual = backpack->commands_lst[backpack->n].arguments;
    if(i == (int)backpack->len && ft_is_space(command[backpack->len + 1]))
        return;
    token = ft_substr(command, i, backpack->len - i);
    if(ft_strchr(token, 36))
    {
        ft_exp_var(backpack, token);
        free(token);
        return;
    }
    temp = ft_lstnew(token);
    ft_lstadd_back(&backpack->commands_lst[backpack->n].arguments, temp);
}

void    ft_save_command(t_backpack *backpack, char *command, int i)
{
    char *token;
    
    if(i == (int)backpack->len)
    {
        backpack->commands_lst[backpack->n].command = NULL;
        return;
    }
    token = ft_substr(command, i, backpack->len - i);
    if(ft_strchr(token, 36))
    {
        ft_exp_var(backpack, token);
        free(token);
        return;
    }
    backpack->commands_lst[backpack->n].command = token;
}
