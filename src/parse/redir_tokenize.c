/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:46:20 by porellan          #+#    #+#             */
/*   Updated: 2025/08/15 19:33:29 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_save_redir(t_bp *bp)
{
	bp->new_redir = malloc(sizeof(t_redir));
	if (!bp->new_redir)
		return ;
	if (bp->red_flag == 1)
		bp->new_redir->op = ft_strdup(">");
	if (bp->red_flag == 2)
		bp->new_redir->op = ft_strdup("<");
	if (bp->red_flag == 3)
		bp->new_redir->op = ft_strdup(">>");
	if (bp->red_flag == 4)
		bp->new_redir->op = ft_strdup("<<");
	bp->new_redir->del = bp->token;
	bp->new_redir->next = NULL;
	if (!bp->commands_lst[bp->n].redirection)
		bp->commands_lst[bp->n].redirection = bp->new_redir;
	else
	{
		bp->tmp = bp->commands_lst[bp->n].redirection;
		while (bp->tmp->next)
			bp->tmp = bp->tmp->next;
		bp->tmp->next = bp->new_redir;
	}
	bp->red_flag = 0;
	bp->token = NULL;
}

void	ft_redirections(t_bp *bp, char *command)
{
	bp->i = (int)bp->len;
	while (!ft_is_redirct(command[bp->len + 1]))
		bp->len++;
	if (bp->len - bp->i == 1)
	{
		if (command[bp->i] == '<')
			bp->red_flag = 4;
		if (command[bp->i] == '>')
			bp->red_flag = 3;
	}
	else
	{
		if (command[bp->i] == '<')
			bp->red_flag = 2;
		if (command[bp->i] == '>')
			bp->red_flag = 1;
	}
	bp->len++;
	bp->i = (int)bp->len;
}
