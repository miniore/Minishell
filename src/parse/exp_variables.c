/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:43:39 by miniore           #+#    #+#             */
/*   Updated: 2025/08/15 19:44:58 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_exp_var(t_bp *bp, char *token)
{
	int		i;
	int		s;

	bp->r_tok = NULL;
	i = 0;
	if (!token[i + 1] && token[i] == '$')
		return (bp->r_tok = ft_strdup("$"));
	while (token[i])
	{
		s = i;
		while (token[i] && token[i] != '$')
			i++;
		if (i > s && !bp->r_tok)
			bp->r_tok = ft_substr(token, s, i - s);
		else if (i > s)
			bp->r_tok = ft_strjoin_free(bp->r_tok, ft_substr(token, s, i - s));
		if (token[i] == '$')
			ft_var_found(bp, token, &i, &s);
	}
	if (!bp->r_tok)
		return (ft_strdup(""));
	return (bp->r_tok);
}
