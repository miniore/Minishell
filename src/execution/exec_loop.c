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

void	exec_singels(t_backpack *backpack, char **envp, t_env *path);
void	exec_pipes(t_backpack *backpack, char **envp, t_env *path);
int		is_buidins(t_backpack *backpack);

int	exec_loop(t_backpack *backpack, char **envp)
{
	t_env	*path;

	path = search_node(&backpack->env, "PATH");
	backpack->n = 0;
	if (backpack->commands_nb == 1)
		exec_singels(backpack, envp, path);
	else
		exec_pipes(backpack, envp, path);
	if (!backpack->err_flag)
		backpack->exit_status = 0;
	return (1);
}

int	ft_pipe_father(t_backpack *backpack, char **envp, t_env *path, int prev_fd)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (backpack->n < (int)backpack->commands_nb - 1)
		if (pipe(pipe_fd) == -1)
			ft_put_syserr_exit(backpack, "Minichelita");
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		ft_put_syserr_exit(backpack, "Minichelita");
	else if (pid == 0)
		ft_pipe_son(backpack, prev_fd, pipe_fd, envp, path);
	else
	{
		waitpid(pid, &status, 0);
		if (prev_fd != -1)
			close(prev_fd);
		if (backpack->n < (int)backpack->commands_nb - 1)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
	}
	return (prev_fd);
}

void	exec_pipes(t_backpack *backpack, char **envp, t_env *path)
{
	int	prev_fd;

	prev_fd = -1;
	backpack->n = 0;
	while (backpack->n < (int)backpack->commands_nb)
	{
		prev_fd = ft_pipe_father(backpack, envp, path, prev_fd);
		backpack->n++;
	}
}

int	is_buidins(t_backpack *backpack)
{
	if (ft_strcmp(backpack->commands_lst[backpack->n].command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(backpack->commands_lst[backpack->n].command, "echo") == 0)
		return (1);
	else if (ft_strcmp(backpack->commands_lst[backpack->n].command, "cd") == 0)
		return (1);
	else if (ft_strcmp(backpack->commands_lst[backpack->n].command, "exit") == 0)
		return (1);
	else if (ft_strcmp(backpack->commands_lst[backpack->n].command, "env") == 0)
		return (1);
	else if (ft_strcmp(backpack->commands_lst[backpack->n].command, "export") == 0)
		return (1);
	else if (ft_strcmp(backpack->commands_lst[backpack->n].command, "unset") == 0)
		return (1);
	return (0);
}

void	exec_singels(t_backpack *backpack, char **envp, t_env *path)
{
	pid_t	p_id;
	int		status;

	backpack->n = 0;
	if (backpack->commands_lst[0].command != NULL)
	{
		if (is_buidins(backpack) == 1)
			ft_bin_singel(backpack, envp, path);
		else
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_IGN);
			p_id = fork();
			if (p_id == -1)
				ft_put_syserr_exit(backpack, "Minichelita");
			else if (p_id == 0)
			{
				ft_cmond_singel(backpack, envp, path);
			}
			waitpid(p_id, &status, 0);
			backpack->exit_status = errno;
		}
	}
}
