/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:46:20 by porellan          #+#    #+#             */
/*   Updated: 2025/06/24 22:41:29 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	redir_add_last(t_redir **lst, t_redir *new)
// {
// 	t_redir	*act;

// 	if (!*lst)
// 		*lst = new;
// 	else
// 	{
// 		act = *lst;
// 		while (act->next != NULL)
// 			act = act->next;
// 		act->next = new;
//         new->prev = act;
// 	}
// }

// t_redir *new_redir_node(char *token)
// {
//     t_redir *node;

//     node = (t_env *) malloc (sizeof(t_env));
//     if (!node)
//         return (NULL);
//     node->var = var;
//     node->content = content;
//     node->prev = NULL;
//     node->next = NULL;
//     return (node);
// }

// static void    ft_get_file(t_backpack *backpack, char *command)
// {
//     backpack->token = NULL;
//     while(ft_is_space(command[backpack->len]) && ft_is_redirct(command[backpack->len]) &&
//             command[backpack->len] != '\0')
//         backpack->len++;
//     printf("EYYY\n");
//     backpack->token = ft_substr(command, backpack->i, backpack->len - backpack->i);
//     backpack->commands_lst[backpack->n].redirection->del = backpack->token;
//     backpack->i = (int)backpack->len;
// }

void    ft_redirections(t_backpack *backpack, char *command)
{
    backpack->new_redir = malloc(sizeof(t_redir));
    if (!backpack->new_redir)
        return;
    backpack->new_redir->op = NULL;
    backpack->new_redir->del = NULL;
    backpack->new_redir->next = NULL;
    //backpack->commands_lst[backpack->n].redirection = (t_redir *)ft_calloc(backpack->commands_nb, sizeof(t_redir));
    // if(!backpack->commands_lst[backpack->n].redirection)
    //     return ;
    while(!ft_is_redirct(command[backpack->len + 1]))
        backpack->len++;
    if(backpack->len - backpack->i > 1 || (backpack->len - backpack-> i == 1 &&
            command[backpack->len - 1] != command[backpack->len]))
    {
        printf("bash: syntax error near redirection token.");
        return;
    }
    backpack->len++;
    backpack->token = ft_substr(command, backpack->i, backpack->len - backpack->i);
    backpack->new_redir->op = backpack->token;
    //backpack->new_redir->op = ft_substr(command, backpack->i, backpack->len - backpack->i);
    while(!ft_is_space(command[backpack->len]))
        backpack->len++;
    backpack->i = (int)backpack->len;
    if(command[backpack->len] == '\0')
        return ;
    //ft_get_file(backpack, command);
    while (command[backpack->len] && ft_is_space(command[backpack->len]) && ft_is_redirct(command[backpack->len]))
        backpack->len++;
    backpack->new_redir->del = ft_substr(command, backpack->i, backpack->len - backpack->i);
    if (!backpack->commands_lst[backpack->n].redirection)
        backpack->commands_lst[backpack->n].redirection = backpack->new_redir;
    else
    {
        backpack->tmp = backpack->commands_lst[backpack->n].redirection;
        while (backpack->tmp->next)
            backpack->tmp = backpack->tmp->next;
        backpack->tmp->next = backpack->new_redir;
    }
    backpack->red_flag = 1;
}

// void    ft_redirections(t_backpack *backpack, char *command)
// {
//     size_t  i;

//     i = backpack->len;

//     while(!ft_is_redirct(command[i + 1]))
//         i++;
//     if(i - backpack->len > 1 || (i - backpack->len == 1 &&
//             command[i - 1] != command[i]))
//     {
//         printf("bash: syntax error near redirection token.");
//         return;
//     }
//     if(i - backpack->len == 1)
//     {
//         if(command[i] == '<')
//             backpack->red_flag = 4;
//         if(command[i] == '>')
//             backpack->red_flag = 3;
//     }
//     else
//     {
//         if(command[i] == '<')
//             backpack->red_flag = 2;
//         if(command[i] == '>')
//             backpack->red_flag = 1;
//     }
//     //backpack->len++;
// }
