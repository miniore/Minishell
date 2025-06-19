/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:46:20 by porellan          #+#    #+#             */
/*   Updated: 2025/06/19 20:40:16 by miniore          ###   ########.fr       */
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
    t_redir *new_redir;
    t_redir *tmp;

    new_redir = malloc(sizeof(t_redir));
    if (!new_redir)
        return;
    new_redir->op = NULL;
    new_redir->del = NULL;
    new_redir->next = NULL;
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
    // backpack->token = ft_substr(command, backpack->i, backpack->len - backpack->i);
    // backpack->commands_lst[backpack->n].redirection->op = backpack->token;
    new_redir->op = ft_substr(command, backpack->i, backpack->len - backpack->i);
    while(!ft_is_space(command[backpack->len]))
        backpack->len++;
    backpack->i = (int)backpack->len;
    // if(command[backpack->len] == '\0')
    //     return;
    //ft_get_file(backpack, command);
    while (command[backpack->len] && ft_is_space(command[backpack->len]) && ft_is_redirct(command[backpack->len]))
        backpack->len++;
    new_redir->del = ft_substr(command, backpack->i, backpack->len - backpack->i);
    if (!backpack->commands_lst[backpack->n].redirection)
        backpack->commands_lst[backpack->n].redirection = new_redir;
    else
    {
        tmp = backpack->commands_lst[backpack->n].redirection;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_redir;
    }
    backpack->red_flag = 1;
}
