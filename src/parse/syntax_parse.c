/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:39:38 by porellan          #+#    #+#             */
/*   Updated: 2025/08/07 21:19:22 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_redir_syntax(char *input)
{
    size_t len;

    len = 0;
    while(input[len])
    {
        while(input[len] && ft_is_redirct(input[len]))
        {
            if(!ft_is_quotes(input[len]) || !ft_is_dquotes(input[len]))
                len = ft_ignore_qargs(input, len);
            len++;
        }
        if(!ft_is_redirct(input[len]))
        {
            len++;
            if((!ft_is_redirct(input[len]) && !ft_is_redirct(input[len + 1])) ||
                    (!ft_is_redirct(input[len]) && (input[len - 1] != input[len])))
                return(EXIT_FAILURE);            
        }
    }
    return(EXIT_SUCCESS);
}

int	ft_quotes_syntax(char *input)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while(input[i] != '\0')
	{
		if(!ft_is_quotes(input[i]))
        {
            flag = 1;
            i++;
            while(ft_is_quotes(input[i]) && input[i] != '\0')
                i++;
            if(!ft_is_quotes(input[i]))
                flag = 0;
        }
		if(!ft_is_dquotes(input[i]))
        {
            flag = 1;
            i++;
            while(ft_is_dquotes(input[i]) && input[i] != '\0')
                i++;
            if(!ft_is_dquotes(input[i]))
                flag = 0;
        }
		if(flag == 1)
			return(EXIT_FAILURE);
		i++;
	}
	return(EXIT_SUCCESS);
}

int ft_pipe_syntax(char *input)
{
    size_t len = 0;

    while(!ft_is_space(input[len]))
        len++;
    if(input[len] == '|')
        return(EXIT_FAILURE);
    while(input[len] != '\0')
    {
        if(input[len] == '|' && input[len + 1] != '|')
            len++;
        else if(input[len] == '|' && input[len + 1] == '|')
            return (EXIT_FAILURE);
        while(!ft_is_space(input[len]))
            len++;
        if(input[len] == '|' || input[len] == '\0')
            return(EXIT_FAILURE);
        while(input[len] != '|' && input[len] != '\0')
        {
            if(!ft_is_quotes(input[len]) || !ft_is_dquotes(input[len]))
                len = ft_ignore_qargs(input, len);
            len++;
        }
        if(input[len] == '|')
        {
            len++;
            if(input[len] == '\0')
                return(EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}

int ft_syntax_parse(t_backpack *backpack, char *input)
{
    if(ft_quotes_syntax(input))
    {
        ft_put_pererr(backpack, "Minichelita: quotes syntax error\n", 258);
        return(EXIT_FAILURE);
    }
    if(ft_pipe_syntax(input))
    {
        ft_put_pererr(backpack , "Minichelita: syntax error near unexpected token `|'\n", 258);
        return(EXIT_FAILURE);
    }
    if(ft_redir_syntax(input))
    {
        ft_put_pererr(backpack, "Minichelita: syntax error near redirection token.\n", 258);
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}
