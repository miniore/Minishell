/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:58:26 by porellan          #+#    #+#             */
/*   Updated: 2025/02/24 19:15:40 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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