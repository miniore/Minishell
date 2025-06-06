/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:12:52 by miniore           #+#    #+#             */
/*   Updated: 2025/06/06 20:52:23 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void  ft_exp_arg(t_backpack *backpack, char *command, int i)
// {
//     i++;
//     ft_extract_content(backpack, command);
//     ft_save_arg(backpack, command, i);
//     backpack->len++;
// }

static void    ft_extract_tokens(t_backpack *backpack, char *command)
{
    t_list  *temp;
    int     i;
    char    *token;
    char    *aux_str;
    
    backpack->cmd_flag = 0;
    backpack->len = 0;
    while (command[backpack->len] != '\0')
    {
        token = NULL;
        while(!ft_is_space(command[backpack->len]))
            backpack->len++;
        if(command[backpack->len] == '\0')
            return ;
        i = (int)backpack->len;
        while (ft_is_space(command[backpack->len]) && command[backpack->len] != '\0')
        {
            if(!ft_is_quotes(command[backpack->len]))
            {
                if(!token)
                    token = ft_substr(command, i, backpack->len - i);
                i = (int)backpack->len + 1;
                ft_extract_content(backpack, command);
                aux_str = ft_substr(command, i, backpack->len - i);
                token = ft_strjoin(token, aux_str);
                backpack->len++;
                i = (int)backpack->len;
                free(aux_str);
            }
            if(!ft_is_dquotes(command[backpack->len]))
            {
                if(!token)
                    token = ft_substr(command, i, backpack->len - i);
                i = (int)backpack->len + 1;
                ft_extract_content(backpack, command);     //detectar exp var aqui dentro??
                aux_str = ft_substr(command, i, backpack->len - i);   //o despues de esto???
                token = ft_strjoin(token, aux_str);
                backpack->len++;
                i = (int)backpack->len;
                free(aux_str);
            }
            while(ft_is_space(command[backpack->len]) && ft_is_dquotes(command[backpack->len]) &&
                    ft_is_quotes(command[backpack->len]) && command[backpack->len] != '\0')    // && command[len] != 60 && command[len] != 62
                backpack->len++;
            if((int)backpack->len > i)
            {
                if(!token)
                    token = ft_substr(command, i, backpack->len - i);
                else
                {
                    aux_str = ft_substr(command, i, backpack->len - i);
                    // if(ft_strchr(aux_str, 36))
                    // {
                    //     //exp var
                    // }
                    token = ft_strjoin(token, aux_str);
                    free(aux_str);
                }
            }
        }
        temp = ft_lstnew(token);
        if(backpack->cmd_flag == 0)
        {
            backpack->commands_lst[backpack->n].command = token;
            backpack->cmd_flag = 1;
        }
        else
            ft_lstadd_back(&backpack->commands_lst[backpack->n].arguments, temp);

        //free(token);
        //echo hola"$USER"aaa'$USER'adios
        
        // if(!ft_is_quotes(command[backpack->len]))
        //     ft_save_qarg(backpack, command, i);
        // else if(!ft_is_dquotes(command[backpack->len]))
        //     ft_exp_arg(backpack, command, i);
        // else
        // {
        //     ft_save_arg(backpack, command, i);
        // }
    }
}

// static void ft_extract_command(t_backpack *backpack, char *command)
// {
//     int     i;

//     i = 0;
//     backpack->flag = 0;
//     while(!ft_is_space(command[i]))
//         i++;
//     while((!ft_is_quotes(command[i]) && !ft_is_quotes(command[i + 1])) ||
//             (!ft_is_dquotes(command[i]) && !ft_is_dquotes(command[i + 1])))
//         i += 2;
//     backpack->len = (size_t)i;
//     // if(!ft_is_quotes(command[i]) || !ft_is_dquotes(command[i])) //REVISAR ESTO!!!
//     //     ft_exp_arg(backpack, command, i);
//     while(ft_is_space(command[backpack->len]) && command[backpack->len] != '\0')
//         backpack->len++;
//     ft_save_command(backpack, command, i);
//     // while(!ft_is_space(command[backpack->len]) && command[backpack->len] != '\0')
//     //     backpack->len++;
//     backpack->flag = 1;
// }

int ft_tokenize(t_backpack *backpack, char *command)
{
    //ft_extract_command(backpack, command);
    if(command[backpack->len] != '\0')
        ft_extract_tokens(backpack, command);
    return(EXIT_SUCCESS);
}
