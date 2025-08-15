/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:09:57 by porellan          #+#    #+#             */
/*   Updated: 2025/08/15 19:21:56 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_join_tok(t_backpack *backpack, char *res_tok, char *var)
{
	char	*var_value;

	var_value = ft_get_var_value(backpack->env, var);
	if (var_value)
	{
		if (!res_tok)
			res_tok = var_value;
		else
			res_tok = ft_strjoin_free(res_tok, var_value);
	}
	return (res_tok);
}

static char	*ft_pid_var(char *token, char *res_tok, int *i, int *start)
{
	int	aux;

	aux = *i;
	if (!res_tok)
		res_tok = ft_itoa(getpid());
	else
		res_tok = ft_strjoin_free(res_tok, ft_itoa(getpid()));
	aux++;
	if (token[aux] && token[aux] != '$')
	{
		*start = aux;
		while (token[aux] && token[aux] != '$')
			aux++;
		res_tok = ft_strjoin_free(res_tok, ft_substr(token, *start, aux - *start));
	}
	*i = aux;
	return (res_tok);
}

static char	*ft_es_var(t_backpack *backpack, char *res_tok, int *i)
{
	int	aux;

	aux = *i;
	if (!res_tok)
		res_tok = ft_itoa(backpack->exit_status);
	else
		res_tok = ft_strjoin_free(res_tok, ft_itoa(backpack->exit_status));
	aux++;
	*i = aux;
	return (res_tok);
}

static char	*ft_invalid_var(char *token, char *res_tok, int *i, int *start)
{
	int	aux;

	aux = *i;
	*start = aux;
	while (token[aux] && token[aux] != '$')
		aux++;
	if (!res_tok)
	{
		res_tok = ft_strdup("$");
		res_tok = ft_strjoin_free(res_tok, ft_substr(token, *start, aux - *start));
	}
	else
	{
		res_tok = ft_strjoin_free(res_tok, ft_strdup("$"));
		res_tok = ft_strjoin_free(res_tok, ft_substr(token, *start, aux - *start));
	}
	*i = aux;
	return (res_tok);
}

void	ft_var_found(t_backpack *backpack, char *token, int *i, int *start)
{
	char	*var;

	var = NULL;
	(*i)++;
	if (token[*i] == '$')
		backpack->res_tok = ft_pid_var(token, backpack->res_tok, i, start);
	else if (token[*i] == '?')
		backpack->res_tok = ft_es_var(backpack, backpack->res_tok, i);
	else if (token[*i] && (ft_isalpha(token[*i]) || token[*i] == '_'))
	{
		*start = *i;
		while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
			(*i)++;
		var = ft_substr(token, *start, *i - *start);
		backpack->res_tok = ft_join_tok(backpack, backpack->res_tok, var);
		free(var);
		var = NULL;
	}
	else if (token[*i] && (!ft_isalnum(token[*i]) || token[*i] != '_'))
		backpack->res_tok = ft_invalid_var(token, backpack->res_tok, i, start);
	else if (!token[*i])
		backpack->res_tok = ft_strjoin_free(backpack->res_tok, ft_strdup("$"));
}
