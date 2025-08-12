/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:43:39 by miniore           #+#    #+#             */
/*   Updated: 2025/08/05 19:02:32 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_get_var_value(t_env *env, char *var_name)
{
    t_env   *node;
    char    *value;
    
    node = search_node(&env, var_name);
    if(!node)
        return(NULL);
    value = ft_strdup(node->content);
    return(value);
}

static char *ft_join_tok(t_backpack *backpack, char *res_tok, char *var)
{
    char    *var_value;

    var_value = ft_get_var_value(backpack->env, var);
    if(var_value)
    {
        if(!res_tok)
            res_tok = var_value;
        else
            res_tok = ft_strjoin_free(res_tok, var_value);
    }
    return(res_tok);
}

char *ft_exp_var(t_backpack *backpack, char *token)
{
    char    *res_tok = NULL;
    char    *var = NULL;
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
        {
            i++;
            if (token[i] == '$')
            {
                if(!res_tok)
                    res_tok = ft_itoa(getpid());
                else
                    res_tok = ft_strjoin_free(res_tok, ft_itoa(getpid()));
                i++;
                if(token[i] && token[i] != '$')
                {
                    start = i;
                    while (token[i] && token[i] != '$')
                        i++;
                    res_tok = ft_strjoin_free(res_tok, ft_substr(token, start, i - start));
                }
            }
            else if (token[i] == '?')
            {
                if(!res_tok)
                    res_tok = ft_itoa(backpack->exit_status);
                else
                    res_tok = ft_strjoin_free(res_tok, ft_itoa(backpack->exit_status));
                i++;
            }
            else if (token[i] && (ft_isalpha(token[i]) || token[i] == '_'))
            {
                start = i;
                while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
                    i++;
                var = ft_substr(token, start, i - start);
                res_tok = ft_join_tok(backpack, res_tok, var);
                free(var);
                var = NULL;
            }
            else if(token[i] && (!ft_isalnum(token[i]) || token[i] != '_'))
            {
                start = i;
                while(token[i] && token[i] != '$')
                    i++;
                if(!res_tok)
                {
                    res_tok = ft_strdup("$");
                    res_tok = ft_strjoin_free(res_tok, ft_substr(token, start, i - start));
                }
                else
                {
                    res_tok = ft_strjoin_free(res_tok, ft_strdup("$"));
                    res_tok = ft_strjoin_free(res_tok, ft_substr(token, start, i - start));
                }
            }
            else if(!token[i])
                res_tok = ft_strjoin_free(res_tok, ft_strdup("$"));
        }
    }
    if (!res_tok)
        return (ft_strdup(""));
    return (res_tok);
}
