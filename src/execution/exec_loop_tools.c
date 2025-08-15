/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:11:56 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/15 20:03:00 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmond_singel(t_bp *bp, char **envp, t_env *path)
{
	signal(SIGINT, handle_ctrl_c);
	if (!bp->commands_lst[bp->n].redirection)
		process_tok(bp, path, envp);
	else
	{
		if (ft_exec_redir(bp, bp->commands_lst[bp->n].redirection) != 0)
		{
			ft_put_syserr(bp, "Minichelita");
			ft_exit_free(bp);
		}
		else
			process_tok(bp, path, envp);
	}
}

void	ft_bin_singel(t_bp *bp, char **envp, t_env *path)
{
	pid_t	p_id;
	int		status;

	if (!bp->commands_lst[bp->n].redirection)
		executor(bp, envp, path);
	else
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_IGN);
		p_id = fork();
		if (p_id == 0)
		{
			signal(SIGINT, handle_ctrl_c);
			if (ft_exec_redir(bp, bp->commands_lst[bp->n].redirection) != 0)
				ft_put_syserr(bp, "Minichelita");
			else
				executor(bp, envp, path);
			ft_exit_free(bp);
		}
		waitpid(p_id, &status, 0);
	}
}

static void	ft_com_last_hdocs(t_bp *bp, int prev_fd)
{
	if (ft_n_hdocs(bp->commands_lst[bp->n].redirection) == 0)
	{
		if (prev_fd != -1)
		{
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
		}
	}
	else if (prev_fd != -1)
		close(prev_fd);
}

static void	ft_pipe_redir(t_bp *bp, int prev_fd, int *pipe_fd)
{
	ft_com_last_hdocs(bp, prev_fd);
	if (ft_exec_redir(bp, bp->commands_lst[bp->n].redirection) != 0)
	{
		ft_put_syserr(bp, "Minichelita");
		if (bp->n < (int)bp->commands_nb - 1)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		ft_exit_free(bp);
	}
	if (ft_n_redout(bp->commands_lst[bp->n].redirection) == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

void	ft_pipe_son(t_bp *bp, int prev_fd, int *pipe_fd, char **envp)
{
	t_env	*path;

	path = search_node(&bp->env, "PATH");
	signal(SIGINT, handle_ctrl_c);
	if (!bp->commands_lst[bp->n].redirection)
	{
		if (prev_fd != -1)
		{
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
		}
		if (bp->n < (int)bp->commands_nb - 1)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
	}
	else
		ft_pipe_redir(bp, prev_fd, pipe_fd);
	executor(bp, envp, path);
	ft_exit_free(bp);
}
