/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_syntax_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:03:10 by porellan          #+#    #+#             */
/*   Updated: 2025/08/15 18:27:08 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_syntax(char *input)
{
	size_t	len;

	len = 0;
	while (input[len])
	{
		while (input[len] && ft_is_redirct(input[len]))
		{
			if (!ft_is_quotes(input[len]) || !ft_is_dquotes(input[len]))
				len = ft_ignore_qargs(input, len);
			len++;
		}
		if (!ft_is_redirct(input[len]))
		{
			len++;
			if ((!ft_is_redirct(input[len]) && !ft_is_redirct(input[len + 1]))
				|| (!ft_is_redirct(input[len]) && (input[len - 1] != input[len])))
				return (EXIT_FAILURE);
			len++;
			while (input[len] && !ft_is_space(input[len]))
				len++;
			if (!input[len] || !ft_is_redirct(input[len]) || input[len] == '|')
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
