/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:05:27 by miniore           #+#    #+#             */
/*   Updated: 2025/08/28 16:21:14 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redir_out(t_redir *redirection, int flag)
{
	int	fd;

	if (flag)
		fd = open(redirection->del, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(redirection->del, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static int	ft_redir_in(t_redir *redirection)
{
	int	fd;

	fd = open(redirection->del, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (ft_lst_rdo(redirection) == 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
		close(fd);
	return (EXIT_SUCCESS);
}

static void	ft_redir_heredoc(t_bp *bp, t_redir *redirection, int exec)
{
	int		pipe_fd[2];
	int		dup_fd;
	char	buffer[102400];

	if (pipe(pipe_fd) == -1)
		ft_put_syserr_exit(bp, "Minishell");
	rl_clear_history();
	dup_fd = dup(STDIN_FILENO);
	while (g_exit_status != 130)
	{
		if (fr_input_handler(bp, redirection, pipe_fd[1]) != 0)
			break ;
	}
	if (g_exit_status == 130 && exec == 1)
	{
		write(pipe_fd[1], " ", 1);
		read(pipe_fd[0], buffer, sizeof(buffer));
	}
	close(pipe_fd[1]);
	if (exec == 1)
		dup2(pipe_fd[0], STDIN_FILENO);
	if (g_exit_status == 130 && exec == 0)
		dup2(dup_fd, STDIN_FILENO);
	close(pipe_fd[0]);
	close(dup_fd);
}

static void	ft_exec_hdoc(t_bp *bp, t_redir *redirection)
{
	t_redir	*iter;
	int		i;
	int		j;

	i = 0;
	j = 1;
	iter = redirection;
	while (iter)
	{
		if (ft_strcmp(iter->op, "<<") == 0)
			i++;
		iter = iter->next;
	}
	while (redirection)
	{
		if (ft_strcmp(redirection->op, "<<") == 0)
		{
			if (j == i)
				ft_redir_heredoc(bp, redirection, 1);
			else
				ft_redir_heredoc(bp, redirection, 0);
			j++;
		}
		redirection = redirection->next;
	}
}

int	ft_exec_redir(t_bp *bp, t_redir *redirection)
{
	ft_exec_hdoc(bp, redirection);
	while (redirection)
	{
		if (ft_strcmp(redirection->op, "<") == 0)
		{
			if (ft_redir_in(redirection))
				return (EXIT_FAILURE);
		}
		if (ft_strcmp(redirection->op, ">") == 0)
			ft_redir_out(redirection, 0);
		if (ft_strcmp(redirection->op, ">>") == 0)
			ft_redir_out(redirection, 1);
		redirection = redirection->next;
	}
	return (EXIT_SUCCESS);
}
