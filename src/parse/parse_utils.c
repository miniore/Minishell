/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:28:47 by miniore           #+#    #+#             */
/*   Updated: 2025/07/29 20:40:24 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strjoin_free(char *s1, char *s2)
{
	char *joined;

    joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

void ft_save_tok(t_backpack *backpack)
{
    t_list  *temp;
    char    *result;
    
    if(backpack->red_flag && backpack->token)
        ft_save_redir(backpack);
    else if(!backpack->red_flag && backpack->token)
    {
        result = ft_strdup(backpack->token);
        if(backpack->cmd_flag == 0)
        {
            backpack->commands_lst[backpack->n].command = result;
            backpack->cmd_flag = 1;
        }
        else
        {
            temp = ft_lstnew(result);
            ft_lstadd_back(&backpack->commands_lst[backpack->n].arguments, temp);
        }
        free(backpack->token);
        backpack->token = NULL;
    }
}

void	ft_extract_content(t_backpack *backpack, char *command)
{
	if(!ft_is_quotes(command[backpack->len]))
    {
        backpack->len++;
		while (ft_is_quotes(command[backpack->len]) && command[backpack->len] != '\0')
            backpack->len++;
    }
    else if(!ft_is_dquotes(command[backpack->len]))
    {
        backpack->len++;
		while (ft_is_dquotes(command[backpack->len]) && command[backpack->len] != '\0')
            backpack->len++;
    }
}

size_t	ft_ignore_qargs(char *command, size_t len)
{
	if(!ft_is_quotes(command[len]))
    {
        while (ft_is_quotes(command[len + 1]) && command[len] != '\0')
            len++;
        len++;
    }
    if(!ft_is_dquotes(command[len]))
    {
        while (ft_is_dquotes(command[len + 1]) && command[len] != '\0')
            len++;
        len++;
    }
    return(len);
}
