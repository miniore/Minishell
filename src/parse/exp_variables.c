/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:43:39 by miniore           #+#    #+#             */
/*   Updated: 2025/08/15 15:10:22 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_exp_var(t_backpack *backpack, char *token)
{
    char    *res_tok = NULL;
    int     i = 0;
    int     start;

    if(!token[i + 1] && token[i] == '$')
        return(res_tok = ft_strdup("$"));
    while (token[i])
    {
        start = i;
        while (token[i] && token[i] != '$')
            i++;
        if(i > start && !res_tok)
            res_tok = ft_substr(token, start, i - start);
        else if (i > start)
            res_tok = ft_strjoin_free(res_tok, ft_substr(token, start, i - start));
        if (token[i] == '$')
            res_tok = ft_var_found(backpack, token, res_tok, &i, &start);
    }
    if (!res_tok)
        return (ft_strdup(""));
    return (res_tok);
}
