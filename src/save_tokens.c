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

#include "../include/minishell.h"

size_t  ft_save_qarg(tok_lst *com_tokens, char *command, int i, size_t len)
{
    t_list  *temp;
    char    *token;

    i++;
    len = ft_extract_content(command, len);
    token = ft_substr(command, i, len - i);
    temp = ft_lstnew(token);
    ft_lstadd_back(&com_tokens->arguments, temp);
    len++;
    //free(token);
    return(len);
}

void    ft_save_arg(tok_lst *com_tokens, char *command, int i, size_t len)
{
    t_list  *temp;
    char    *token;

    if(i == (int)len && ft_is_space(command[len + 1]))
        return;
    token = ft_substr(command, i, len - i);
    if(ft_strchr(token, 36))
    {
        ft_exp_var(com_tokens, token);
        free(token);
        return;
    }
    temp = ft_lstnew(token);
    ft_lstadd_back(&com_tokens->arguments, temp);
}

void    ft_save_command(tok_lst *com_tokens, char *command, int i, size_t len)
{
    char *token;
    
    if(i == (int)len)
    {
        com_tokens->command = NULL;
        return;
    }
    token = ft_substr(command, i, len - i);
    if(ft_strchr(token, 36))
    {
        ft_exp_var(com_tokens, token);
        free(token);
        return;
    }
    com_tokens->command = token;
}
