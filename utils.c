/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:58:26 by porellan          #+#    #+#             */
/*   Updated: 2025/02/27 13:02:59 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	is_redirct(char c)
{
	if(c == '<' || c == '>')
		return(EXIT_SUCCESS);
	return(EXIT_FAILURE);
}

int	is_space(char c)
{
	if(c == 32)
		return(EXIT_SUCCESS);
	return(EXIT_FAILURE);
}

int	is_quotes(char c)
{
	if(c == 39)
		return(EXIT_SUCCESS);
	return(EXIT_FAILURE);
}

int	is_dquotes(char c)
{
	if(c == 34)
		return(EXIT_SUCCESS);
	return(EXIT_FAILURE);	
}