/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:12:52 by miniore           #+#    #+#             */
/*   Updated: 2025/08/15 19:32:46 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_quotes_tok(t_bp *bp, char *command)
{
	if (!bp->token)
		bp->token = ft_substr(command, bp->i, bp->len - bp->i);
	bp->i = (int)bp->len + 1;
	ft_extract_content(bp, command);
	bp->str_2_join = ft_substr(command, bp->i, bp->len - bp->i);
	bp->token = ft_strjoin_free(bp->token, bp->str_2_join);
	bp->len++;
	bp->i = (int)bp->len;
	bp->str_2_join = NULL;
}

static void	ft_dquotes_tok(t_bp *bp, char *command)
{
	if (!bp->token)
		bp->token = ft_substr(command, bp->i, bp->len - bp->i);
	bp->i = (int)bp->len + 1;
	ft_extract_content(bp, command);
	bp->str_2_join = ft_substr(command, bp->i, bp->len - bp->i);
	if (ft_strchr(bp->str_2_join, 36))
	{
		bp->aux_str = ft_exp_var(bp, bp->str_2_join);
		bp->token = ft_strjoin_free(bp->token, bp->aux_str);
		free(bp->str_2_join);
		bp->aux_str = NULL;
	}
	else
		bp->token = ft_strjoin_free(bp->token, bp->str_2_join);
	bp->len++;
	bp->i = (int)bp->len;
	bp->str_2_join = NULL;
}

static void	ft_tok(t_bp *bp, char *command)
{
	if (!bp->token)
	{
		bp->aux_str = ft_substr(command, bp->i, bp->len - bp->i);
		if (ft_strchr(bp->aux_str, 36))
		{
			bp->token = ft_exp_var(bp, bp->aux_str);
			free(bp->aux_str);
		}
		else
			bp->token = bp->aux_str;
	}
	else
	{
		bp->str_2_join = ft_substr(command, bp->i, bp->len - bp->i);
		if (ft_strchr(bp->str_2_join, 36))
		{
			bp->aux_str = ft_exp_var(bp, bp->str_2_join);
			bp->token = ft_strjoin_free(bp->token, bp->aux_str);
			free(bp->str_2_join);
			bp->aux_str = NULL;
		}
		else
			bp->token = ft_strjoin_free(bp->token, bp->str_2_join);
		bp->str_2_join = NULL;
	}
}

static void	ft_get_token(t_bp *bp, char *command)
{
	if (!ft_is_quotes(command[bp->len]))
		ft_quotes_tok(bp, command);
	if (!ft_is_dquotes(command[bp->len]))
		ft_dquotes_tok(bp, command);
	while (command[bp->len] && ft_is_space(command[bp->len])
		&& ft_is_dquotes(command[bp->len]) && ft_is_quotes(command[bp->len]))
	{
		if (!ft_is_redirct(command[bp->len]))
		{
			if ((int)bp->len > bp->i)
				ft_tok(bp, command);
			if (!bp->red_flag && bp->token)
				ft_save_tok(bp);
			else if (bp->red_flag && bp->token)
				ft_save_redir(bp);
			ft_redirections(bp, command);
			break ;
		}
		bp->len++;
	}
	if ((int)bp->len > bp->i)
		ft_tok(bp, command);
}

void	ft_extract_tokens(t_bp *bp, char *command)
{
	while (command[bp->len] != '\0')
	{
		bp->token = NULL;
		bp->str_2_join = NULL;
		bp->aux_str = NULL;
		while (!ft_is_space(command[bp->len]))
			bp->len++;
		if (command[bp->len] == '\0')
			return ;
		bp->i = (int)bp->len;
		while (ft_is_space(command[bp->len]) && command[bp->len] != '\0')
			ft_get_token(bp, command);
		ft_save_tok(bp);
	}
}
