/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:29:37 by miniore           #+#    #+#             */
/*   Updated: 2025/03/25 12:29:39 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redirct(char c)
{
	if(c == '<' || c == '>')
		return(EXIT_SUCCESS);
	return(EXIT_FAILURE);
}

int	ft_is_space(char c)
{
	if(c == 32)
		return(EXIT_SUCCESS);
	return(EXIT_FAILURE);
}

int	ft_is_quotes(char c)
{
	if(c == 39)
		return(EXIT_SUCCESS);
	return(EXIT_FAILURE);
}

int	ft_is_dquotes(char c)
{
	if(c == 34)
		return(EXIT_SUCCESS);
	return(EXIT_FAILURE);	
}
