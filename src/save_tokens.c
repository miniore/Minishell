/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:27:59 by miniore           #+#    #+#             */
/*   Updated: 2025/04/02 18:51:19 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t  ft_save_qarg(t_list *backpack, char *command, int i, size_t len)
{
    t_list *actual;
    t_list  *temp;
    char    *token;

    i++;
    actual = backpack->commands_lst->com_tokens->arguments;
    len = ft_extract_content(command, len);
    token = ft_substr(command, i, len - i);
    temp = ft_lstnew(token);
    ft_lstadd_back(&actual, temp);
    len++;
    //free(token);
    return(len);
}

void    ft_save_arg(t_list * backpack, char *command, int i, size_t len)
{
    t_list *actual;
    t_list  *temp;
    char    *token;

    actual = backpack->commands_lst->com_tokens->arguments;
    if(i == (int)len && ft_is_space(command[len + 1]))
        return;
    token = ft_substr(command, i, len - i);
    if(ft_strchr(token, 36))
    {
        ft_exp_var(backpack, token);
        free(token);
        return;
    }
    temp = ft_lstnew(token);
    ft_lstadd_back(&actual, temp);
}

void    ft_save_command(t_list *backpack, char *command, int i, size_t len)
{
    tok_lst *temp;
    char *token;
    
    temp = backpack->commands_lst->com_tokens;
    while(temp->next != NULL)
        temp = temp->next;
    if(i == (int)len)
    {
        temp->command = NULL;
        return;
    }
    token = ft_substr(command, i, len - i);
    if(ft_strchr(token, 36))
    {
        ft_exp_var(backpack, token);
        free(token);
        return;
    }
    tem->command = token;
}
