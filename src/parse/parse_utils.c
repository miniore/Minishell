/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:28:47 by miniore           #+#    #+#             */
/*   Updated: 2025/08/15 19:34:04 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

void	ft_save_tok(t_bp *bp)
{
	t_list	*temp;
	char	*result;

	if (bp->red_flag && bp->token)
		ft_save_redir(bp);
	else if (!bp->red_flag && bp->token)
	{
		result = ft_strdup(bp->token);
		if (bp->cmd_flag == 0)
		{
			bp->commands_lst[bp->n].command = result;
			bp->cmd_flag = 1;
		}
		else
		{
			temp = ft_lstnew(result);
			ft_lstadd_back(&bp->commands_lst[bp->n].arguments, temp);
		}
		free(bp->token);
		bp->token = NULL;
	}
}

void	ft_extract_content(t_bp *bp, char *command)
{
	if (!ft_is_quotes(command[bp->len]))
	{
		bp->len++;
		while (ft_is_quotes(command[bp->len]) && command[bp->len] != '\0')
			bp->len++;
	}
	else if (!ft_is_dquotes(command[bp->len]))
	{
		bp->len++;
		while (ft_is_dquotes(command[bp->len]) && command[bp->len] != '\0')
			bp->len++;
	}
}

size_t	ft_ignore_qargs(char *command, size_t len)
{
	if (!ft_is_quotes(command[len]))
	{
		while (ft_is_quotes(command[len + 1]) && command[len] != '\0')
			len++;
		len++;
	}
	if (!ft_is_dquotes(command[len]))
	{
		while (ft_is_dquotes(command[len + 1]) && command[len] != '\0')
			len++;
		len++;
	}
	return (len);
}

char	*ft_get_var_value(t_env *env, char *var_name)
{
	t_env	*node;
	char	*value;

	node = search_node(&env, var_name);
	if (!node)
		return (NULL);
	value = ft_strdup(node->content);
	return (value);
}
