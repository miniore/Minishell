/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:12:52 by miniore           #+#    #+#             */
/*   Updated: 2025/06/24 22:38:14 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_quotes_tok(t_backpack *backpack, char *command)
{
    if(!backpack->token)
        backpack->token = ft_substr(command, backpack->i, backpack->len - backpack->i);
    backpack->i = (int)backpack->len + 1;
    ft_extract_content(backpack, command);
    backpack->str_2_join = ft_substr(command, backpack->i, backpack->len - backpack->i);
    backpack->token = ft_strjoin(backpack->token, backpack->str_2_join);
    backpack->len++;
    backpack->i = (int)backpack->len;
    free(backpack->str_2_join);
}

static void ft_dquotes_tok(t_backpack *backpack, char *command)
{
    if(!backpack->token)
        backpack->token = ft_substr(command, backpack->i, backpack->len - backpack->i);
    backpack->i = (int)backpack->len + 1;
    ft_extract_content(backpack, command);
    backpack->str_2_join = ft_substr(command, backpack->i, backpack->len - backpack->i);
    if(ft_strchr(backpack->str_2_join, 36))
    {
        backpack->aux_str = ft_exp_var(backpack, backpack->str_2_join);
        backpack->token = ft_strjoin(backpack->token, backpack->aux_str);
        free(backpack->aux_str);
    }
    else
        backpack->token = ft_strjoin(backpack->token, backpack->str_2_join);
    backpack->len++;
    backpack->i = (int)backpack->len;
    free(backpack->str_2_join);
}

static void ft_tok(t_backpack *backpack, char *command)
{
    if(!backpack->token)
    {
        backpack->token = ft_substr(command, backpack->i, backpack->len - backpack->i);
        if(ft_strchr(backpack->token, 36))
            backpack->token = ft_exp_var(backpack, backpack->token);
    }
    else
    {
        backpack->str_2_join = ft_substr(command, backpack->i, backpack->len - backpack->i);
        if(ft_strchr(backpack->str_2_join, 36))
        {
            backpack->aux_str = ft_exp_var(backpack, backpack->str_2_join);
            backpack->token = ft_strjoin(backpack->token, backpack->aux_str);
            free(backpack->aux_str);
        }
        else
            backpack->token = ft_strjoin(backpack->token, backpack->str_2_join);
        free(backpack->str_2_join);
    }
}

static void ft_save_tok(t_backpack *backpack)
{
    t_list  *temp;

    temp = ft_lstnew(backpack->token);
    if(backpack->red_flag == 1)
    {
        
    }
    else if(backpack->cmd_flag == 0)
    {
        backpack->commands_lst[backpack->n].command = backpack->token;
        backpack->cmd_flag = 1;
    }
    else
        ft_lstadd_back(&backpack->commands_lst[backpack->n].arguments, temp);
}

void    ft_extract_tokens(t_backpack *backpack, char *command)
{
    while (command[backpack->len] != '\0')
    {
        backpack->token = NULL;
        backpack->str_2_join = NULL;
        //backpack->red_flag = 0;
        while(!ft_is_space(command[backpack->len]))
            backpack->len++;
        if(command[backpack->len] == '\0')
            return ;
        backpack->i = (int)backpack->len;
        while (ft_is_space(command[backpack->len]) && command[backpack->len] != '\0')
        {
            if(!ft_is_quotes(command[backpack->len]))
                ft_quotes_tok(backpack, command);
            if(!ft_is_dquotes(command[backpack->len]))
                ft_dquotes_tok(backpack, command);
            while(command[backpack->len] && ft_is_space(command[backpack->len]) &&
                    ft_is_dquotes(command[backpack->len]) && ft_is_quotes(command[backpack->len]))
            {
                if(!ft_is_redirct(command[backpack->len]))
                {
                    if((int)backpack->len > backpack->i)
                        ft_tok(backpack, command);
                    ft_save_tok(backpack);
                    ft_redirections(backpack, command);
                    backpack->i = (int)backpack->len;
                    break;
                }
                backpack->len++;
            }
            if((int)backpack->len > backpack->i)
                ft_tok(backpack, command);
        }
        if(backpack->red_flag == 0)    //mirar mejor opcion para juntar las redir en save_tok tambien
            ft_save_tok(backpack);
    }
}
