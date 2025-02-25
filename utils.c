/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:58:26 by porellan          #+#    #+#             */
/*   Updated: 2025/02/25 11:51:09 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	is_redict(char c)
{
	if(c == '<' || c == '>')
		return(EXIT_SUCCESS);
	return(EXIT_FAILURE);
}

int	is_space(char c)
{
	if(c == ' ')
		return(EXIT_SUCCESS);
	return(EXIT_FAILURE);
}