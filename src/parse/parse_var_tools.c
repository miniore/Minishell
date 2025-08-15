/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:09:57 by porellan          #+#    #+#             */
/*   Updated: 2025/08/15 19:45:15 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_join_tok(t_bp *bp, char *r_tok, char *var)
{
	char	*var_value;

	var_value = ft_get_var_value(bp->env, var);
	if (var_value)
	{
		if (!r_tok)
			r_tok = var_value;
		else
			r_tok = ft_strjoin_free(r_tok, var_value);
	}
	return (r_tok);
}

static char	*ft_pid_var(char *token, char *r_tok, int *i, int *s)
{
	int	aux;

	aux = *i;
	if (!r_tok)
		r_tok = ft_itoa(getpid());
	else
		r_tok = ft_strjoin_free(r_tok, ft_itoa(getpid()));
	aux++;
	if (token[aux] && token[aux] != '$')
	{
		*s = aux;
		while (token[aux] && token[aux] != '$')
			aux++;
		r_tok = ft_strjoin_free(r_tok, ft_substr(token, *s, aux - *s));
	}
	*i = aux;
	return (r_tok);
}

static char	*ft_es_var(t_bp *bp, char *r_tok, int *i)
{
	int	aux;

	aux = *i;
	if (!r_tok)
		r_tok = ft_itoa(bp->exit_status);
	else
		r_tok = ft_strjoin_free(r_tok, ft_itoa(bp->exit_status));
	aux++;
	*i = aux;
	return (r_tok);
}

static char	*ft_invalid_var(char *token, char *r_tok, int *i, int *s)
{
	int	aux;

	aux = *i;
	*s = aux;
	while (token[aux] && token[aux] != '$')
		aux++;
	if (!r_tok)
	{
		r_tok = ft_strdup("$");
		r_tok = ft_strjoin_free(r_tok, ft_substr(token, *s, aux - *s));
	}
	else
	{
		r_tok = ft_strjoin_free(r_tok, ft_strdup("$"));
		r_tok = ft_strjoin_free(r_tok, ft_substr(token, *s, aux - *s));
	}
	*i = aux;
	return (r_tok);
}

void	ft_var_found(t_bp *bp, char *token, int *i, int *s)
{
	char	*var;

	var = NULL;
	(*i)++;
	if (token[*i] == '$')
		bp->r_tok = ft_pid_var(token, bp->r_tok, i, s);
	else if (token[*i] == '?')
		bp->r_tok = ft_es_var(bp, bp->r_tok, i);
	else if (token[*i] && (ft_isalpha(token[*i]) || token[*i] == '_'))
	{
		*s = *i;
		while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
			(*i)++;
		var = ft_substr(token, *s, *i - *s);
		bp->r_tok = ft_join_tok(bp, bp->r_tok, var);
		free(var);
		var = NULL;
	}
	else if (token[*i] && (!ft_isalnum(token[*i]) || token[*i] != '_'))
		bp->r_tok = ft_invalid_var(token, bp->r_tok, i, s);
	else if (!token[*i])
		bp->r_tok = ft_strjoin_free(bp->r_tok, ft_strdup("$"));
}
