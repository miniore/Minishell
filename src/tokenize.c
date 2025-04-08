/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:12:52 by miniore           #+#    #+#             */
/*   Updated: 2025/04/03 11:51:14 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t  ft_exp_arg(tok_lst *com_tokens, char *command, int i, size_t len)
{

    i++;
    len = ft_extract_content(command, len);
    ft_save_arg(com_tokens, command, i, len);
    len++;
    return(len);
}

static void    ft_extract_tokens(tok_lst *com_tokens, char *command, size_t len)
{
    int     i;
    
    while (command[len] != '\0')
    {
        while(!ft_is_space(command[len]))
            len++;
        i = (int)len;
        if(!ft_is_quotes(command[len]))
            len = ft_save_qarg(com_tokens, command, i, len);
        else if(!ft_is_dquotes(command[len]))
            len = ft_exp_arg(com_tokens, command, i, len);
        else
        {
            while(ft_is_space(command[len]) && ft_is_dquotes(command[len]) &&
                    ft_is_quotes(command[len]) && command[len] != '\0')    // && command[len] != 60 && command[len] != 62
                len++;
            ft_save_arg(com_tokens, command, i, len);
        }
    }
}

static size_t ft_extract_command(tok_lst *com_tokens, char *command)
{
    size_t     len;
    int     i;

    i = 0;
    while(!ft_is_space(command[i]))
        i++;
    while((!ft_is_quotes(command[i]) && !ft_is_quotes(command[i + 1])) ||
            (!ft_is_dquotes(command[i]) && !ft_is_dquotes(command[i + 1])))
        i += 2;
    len = (size_t)i;
    if(!ft_is_quotes(command[i]) || !ft_is_dquotes(command[i]))
        len = ft_exp_arg(com_tokens, command, i, len);
    else
    {
        while(ft_is_space(command[len]) && command[len] != '\0')
            len++;
        ft_save_command(com_tokens, command, i, len);
    }
    while(!ft_is_space(command[len]) && command[len] != '\0')
        len++;
    return(len);
}

int ft_tokenize(t_list **commands_lst, char *command)
{
    tok_lst *com_tokens;
    size_t  len;
    
    com_tokens = (tok_lst *)ft_calloc(1, sizeof(tok_lst));
    if(!com_tokens)
        return(EXIT_FAILURE);
    len = ft_extract_command(com_tokens, command);
    if(command[len] != '\0')
        ft_extract_tokens(com_tokens, command, len);
    ft_lstadd_back(commands_lst, ft_lstnew(com_tokens));
    return(EXIT_SUCCESS);
}
