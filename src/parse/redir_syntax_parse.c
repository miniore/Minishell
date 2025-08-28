/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_syntax_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@studt.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:03:10 by porellan          #+#    #+#             */
/*   Updated: 2025/08/15 18:27:08 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_len_tool(char *input, size_t l)
{
	if(input[l + 1])
		l++;
	while (input[l] && !ft_is_spotab(input[l]))
		l++;
	return (l);
}

int	ft_redir_syntax(char *input)
{
	size_t	l;

	l = 0;
	while (input[l])
	{
		while (input[l] && ft_is_redirct(input[l]))
		{
			if (!ft_is_quotes(input[l]) || !ft_is_dquotes(input[l]))
				l = ft_ignore_qargs(input, l);
			l++;
		}
		if (!ft_is_redirct(input[l]))
		{
			l++;
			if ((!ft_is_redirct(input[l]) && !ft_is_redirct(input[l + 1]))
				|| (!ft_is_redirct(input[l]) && (input[l - 1] != input[l])))
				return (EXIT_FAILURE);
			l = ft_len_tool(input, l);
			if (!input[l] || !ft_is_redirct(input[l]) || input[l] == '|')
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
