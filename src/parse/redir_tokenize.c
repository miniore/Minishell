/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:46:20 by porellan          #+#    #+#             */
/*   Updated: 2025/07/24 13:57:51 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_save_redir(t_backpack *backpack)
{
    backpack->new_redir = malloc(sizeof(t_redir));
    if (!backpack->new_redir)
        return;
    if(backpack->red_flag == 1)
        backpack->new_redir->op = ft_strdup(">");
    if(backpack->red_flag == 2)
        backpack->new_redir->op = ft_strdup("<");
    if(backpack->red_flag == 3)
        backpack->new_redir->op = ft_strdup(">>");
    if(backpack->red_flag == 4)
        backpack->new_redir->op = ft_strdup("<<");
    backpack->new_redir->del = backpack->token;
    backpack->new_redir->next = NULL;
    if (!backpack->commands_lst[backpack->n].redirection)
        backpack->commands_lst[backpack->n].redirection = backpack->new_redir;
    else
    {
        backpack->tmp = backpack->commands_lst[backpack->n].redirection;
        while (backpack->tmp->next)
            backpack->tmp = backpack->tmp->next;
        backpack->tmp->next = backpack->new_redir;
    }
    backpack->red_flag = 0;
    backpack->token = NULL;
}

void    ft_redirections(t_backpack *backpack, char *command)
{
    backpack->i = (int)backpack->len;
    while(!ft_is_redirct(command[backpack->len + 1]))
        backpack->len++;
    if(backpack->len - backpack->i > 1 || (backpack->len - backpack->i == 1 &&
            command[backpack->len - 1] != command[backpack->len]))
    {
        printf("bash: syntax error near redirection token.");
        return;
    }
    if(backpack->len - backpack->i == 1)
    {
        if(command[backpack->i] == '<')
            backpack->red_flag = 4;
        if(command[backpack->i] == '>')
            backpack->red_flag = 3;
    }
    else
    {
        if(command[backpack->i] == '<')
            backpack->red_flag = 2;
        if(command[backpack->i] == '>')
            backpack->red_flag = 1;
    }
    backpack->len++;
    backpack->i = (int)backpack->len;
}
