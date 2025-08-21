/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:01:59 by frlorenz          #+#    #+#             */
/*   Updated: 2025/06/10 08:23:05 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_singels(t_bp *bp, char **envp, t_env *path);
void	exec_pipes(t_bp *bp, char **envp);
int		is_buidins(t_bp *bp);

int	exec_loop(t_bp *bp, char **envp)
{
	t_env	*path;

	path = search_node(&bp->env, "PATH");
	bp->n = 0;
	if (bp->commands_nb == 1)
		exec_singels(bp, envp, path);
	else
		exec_pipes(bp, envp);
	if (!bp->err_flag)
		bp->exit_status = 0;
	return (1);
}

int	ft_pipe_father(t_bp *bp, char **envp, int prev_fd)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (bp->n < (int)bp->commands_nb - 1)
		if (pipe(pipe_fd) == -1)
			ft_put_syserr_exit(bp, "Minichelita");
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		ft_put_syserr_exit(bp, "Minichelita");
	else if (pid == 0)
		ft_pipe_son(bp, prev_fd, pipe_fd, envp);
	else
	{
		waitpid(pid, &status, 0);
		if (prev_fd != -1)
			close(prev_fd);
		if (bp->n < (int)bp->commands_nb - 1)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
	}
	return (prev_fd);
}

void	exec_pipes(t_bp *bp, char **envp)
{
	int	prev_fd;

	prev_fd = -1;
	bp->n = 0;
	while (bp->n < (int)bp->commands_nb)
	{
		prev_fd = ft_pipe_father(bp, envp, prev_fd);
		bp->n++;
	}
}

int	is_buidins(t_bp *bp)
{
	if (ft_strcmp(bp->commands_lst[bp->n].command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(bp->commands_lst[bp->n].command, "echo") == 0)
		return (1);
	else if (ft_strcmp(bp->commands_lst[bp->n].command, "cd") == 0)
		return (1);
	else if (ft_strcmp(bp->commands_lst[bp->n].command, "exit") == 0)
		return (1);
	else if (ft_strcmp(bp->commands_lst[bp->n].command, "env") == 0)
		return (1);
	else if (ft_strcmp(bp->commands_lst[bp->n].command, "export") == 0)
		return (1);
	else if (ft_strcmp(bp->commands_lst[bp->n].command, "unset") == 0)
		return (1);
	return (0);
}

void	exec_singels(t_bp *bp, char **envp, t_env *path)
{
	pid_t	p_id;
	int		status;

	bp->n = 0;
	if (bp->commands_lst[0].command != NULL)
	{
		if (is_buidins(bp) == 1)
			ft_bin_singel(bp, envp, path);
		else
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_IGN);
			p_id = fork();
			if (p_id == -1)
				ft_put_syserr_exit(bp, "Minichelita");
			else if (p_id == 0)
				ft_cmond_singel(bp, envp, path);
			waitpid(p_id, &status, 0);
			if (status)
				bp->err_flag = 1;
			bp->exit_status = get_exit_status(status);
		}
	}
}
