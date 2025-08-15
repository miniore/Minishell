/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:12:52 by miniore           #+#    #+#             */
/*   Updated: 2025/08/15 18:39:43 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_quotes_tok(t_backpack *backpack, char *command)
{
	if (!backpack->token)
		backpack->token = ft_substr(command, backpack->i, backpack->len - backpack->i);
	backpack->i = (int)backpack->len + 1;
	ft_extract_content(backpack, command);
	backpack->str_2_join = ft_substr(command, backpack->i, backpack->len - backpack->i);
	backpack->token = ft_strjoin_free(backpack->token, backpack->str_2_join);
	backpack->len++;
	backpack->i = (int)backpack->len;
	backpack->str_2_join = NULL;
}

static void	ft_dquotes_tok(t_backpack *backpack, char *command)
{
	if (!backpack->token)
		backpack->token = ft_substr(command, backpack->i, backpack->len - backpack->i);
	backpack->i = (int)backpack->len + 1;
	ft_extract_content(backpack, command);
	backpack->str_2_join = ft_substr(command, backpack->i, backpack->len - backpack->i);
	if (ft_strchr(backpack->str_2_join, 36))
	{
		backpack->aux_str = ft_exp_var(backpack, backpack->str_2_join);
		backpack->token = ft_strjoin_free(backpack->token, backpack->aux_str);
		free(backpack->str_2_join);
		backpack->aux_str = NULL;
	}
	else
		backpack->token = ft_strjoin_free(backpack->token, backpack->str_2_join);
	backpack->len++;
	backpack->i = (int)backpack->len;
	backpack->str_2_join = NULL;
}

static void	ft_tok(t_backpack *backpack, char *command)
{
	if (!backpack->token)
	{
		backpack->aux_str = ft_substr(command, backpack->i, backpack->len - backpack->i);
		if (ft_strchr(backpack->aux_str, 36))
		{
			backpack->token = ft_exp_var(backpack, backpack->aux_str);
			free(backpack->aux_str);
		}
		else
			backpack->token = backpack->aux_str;
	}
	else
	{
		backpack->str_2_join = ft_substr(command, backpack->i, backpack->len - backpack->i);
		if (ft_strchr(backpack->str_2_join, 36))
		{
			backpack->aux_str = ft_exp_var(backpack, backpack->str_2_join);
			backpack->token = ft_strjoin_free(backpack->token, backpack->aux_str);
			free(backpack->str_2_join);
			backpack->aux_str = NULL;
		}
		else
			backpack->token = ft_strjoin_free(backpack->token, backpack->str_2_join);
		backpack->str_2_join = NULL;
	}
}

static void	ft_get_token(t_backpack *backpack, char *command)
{
	if (!ft_is_quotes(command[backpack->len]))
		ft_quotes_tok(backpack, command);
	if (!ft_is_dquotes(command[backpack->len]))
		ft_dquotes_tok(backpack, command);
	while (command[backpack->len] && ft_is_space(command[backpack->len])
		&& ft_is_dquotes(command[backpack->len]) && ft_is_quotes(command[backpack->len]))
	{
		if (!ft_is_redirct(command[backpack->len]))
		{
			if ((int)backpack->len > backpack->i)
				ft_tok(backpack, command);
			if (!backpack->red_flag && backpack->token)
				ft_save_tok(backpack);
			else if (backpack->red_flag && backpack->token)
				ft_save_redir(backpack);
			ft_redirections(backpack, command);
			break ;
		}
		backpack->len++;
	}
	if ((int)backpack->len > backpack->i)
		ft_tok(backpack, command);
}

void	ft_extract_tokens(t_backpack *backpack, char *command)
{
	while (command[backpack->len] != '\0')
	{
		backpack->token = NULL;
		backpack->str_2_join = NULL;
		backpack->aux_str = NULL;
		while (!ft_is_space(command[backpack->len]))
			backpack->len++;
		if (command[backpack->len] == '\0')
			return ;
		backpack->i = (int)backpack->len;
		while (ft_is_space(command[backpack->len]) && command[backpack->len] != '\0')
			ft_get_token(backpack, command);
		ft_save_tok(backpack);
	}
}
