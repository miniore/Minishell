/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:28:47 by miniore           #+#    #+#             */
/*   Updated: 2025/03/27 12:42:29 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_extract_content(char *command, size_t len)
{
	if(!ft_is_quotes(command[len]))
    {
        len++;
		while (ft_is_quotes(command[len]) && command[len] != '\0')
            len++;
    }
    else if(!ft_is_dquotes(command[len]))
    {
        len++;
		while (ft_is_dquotes(command[len]) && command[len] != '\0')
            len++;
    }
	return(len);
}

// static int  ft_check_dquotes(char *input, int i, int flag)
// {
// 	flag = 1;
// 	i++;
// 	while(ft_is_dquotes(input[i]) && input[i] != '\0')
// 		i++;
// 	if(!ft_is_dquotes(input[i]))
// 		flag = 0;
//     return(flag);
// }

// static int  ft_check_quotes(char *input, int i, int flag)
// {
// 	flag = 1;
// 	i++;
// 	while(ft_is_quotes(input[i]) && input[i] != '\0')
// 		i++;
// 	if(!ft_is_quotes(input[i]))
// 		flag = 0;
//     return(flag);
// }

int	ft_syntax_parse(char *input)
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
