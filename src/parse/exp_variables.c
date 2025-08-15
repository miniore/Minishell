/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:43:39 by miniore           #+#    #+#             */
/*   Updated: 2025/08/15 19:21:35 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_exp_var(t_backpack *backpack, char *token)
{
	int		i;
	int		start;

	backpack->res_tok = NULL;
	i = 0;
	if (!token[i + 1] && token[i] == '$')
		return (backpack->res_tok = ft_strdup("$"));
	while (token[i])
	{
		start = i;
		while (token[i] && token[i] != '$')
			i++;
		if (i > start && !backpack->res_tok)
			backpack->res_tok = ft_substr(token, start, i - start);
		else if (i > start)
			backpack->res_tok = ft_strjoin_free(backpack->res_tok, ft_substr(token, start, i - start));
		if (token[i] == '$')
			ft_var_found(backpack, token, &i, &start);
	}
	if (!backpack->res_tok)
		return (ft_strdup(""));
	return (backpack->res_tok);
}
