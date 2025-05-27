/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:12:52 by miniore           #+#    #+#             */
/*   Updated: 2025/05/27 12:14:41 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void  ft_exp_arg(t_backpack *backpack, char *command, int i)
{
    i++;
    ft_extract_content(backpack, command);
    ft_save_arg(backpack, command, i);
    backpack->len++;
}

static void    ft_extract_tokens(t_backpack *backpack, char *command)
{
    int     i;
    
    while (command[backpack->len] != '\0')
    {
        while(!ft_is_space(command[backpack->len]))
            backpack->len++;
        i = (int)backpack->len;
        if(!ft_is_quotes(command[backpack->len]))
            ft_save_qarg(backpack, command, i);
        else if(!ft_is_dquotes(command[backpack->len]))
            ft_exp_arg(backpack, command, i);
        else
        {
            while(ft_is_space(command[backpack->len]) && ft_is_dquotes(command[backpack->len]) &&
                    ft_is_quotes(command[backpack->len]) && command[backpack->len] != '\0')    // && command[len] != 60 && command[len] != 62
                backpack->len++;
            ft_save_arg(backpack, command, i);
        }
    }
}

static void ft_extract_command(t_backpack *backpack, char *command)
{
    int     i;

    i = 0;
    backpack->flag = 0;
    while(!ft_is_space(command[i]))
        i++;
    while((!ft_is_quotes(command[i]) && !ft_is_quotes(command[i + 1])) ||
            (!ft_is_dquotes(command[i]) && !ft_is_dquotes(command[i + 1])))
        i += 2;
    backpack->len = (size_t)i;
    // if(!ft_is_quotes(command[i]) || !ft_is_dquotes(command[i])) //REVISAR ESTO!!!
    //     ft_exp_arg(backpack, command, i);
    while(ft_is_space(command[backpack->len]) && command[backpack->len] != '\0')
        backpack->len++;
    ft_save_command(backpack, command, i);
    // while(!ft_is_space(command[backpack->len]) && command[backpack->len] != '\0')
    //     backpack->len++;
    backpack->flag = 1;
}

int ft_tokenize(t_backpack *backpack, char *command)
{
    ft_extract_command(backpack, command);
    if(command[backpack->len] != '\0')
        ft_extract_tokens(backpack, command);
    return(EXIT_SUCCESS);
}
