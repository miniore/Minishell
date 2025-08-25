/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:59:11 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/25 19:07:42 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_n_hdocs(t_redir *redirection)
{
	int	i;

	i = 0;
	while (redirection)
	{
		if (ft_strcmp(redirection->op, "<<") == 0)
			i++;
		redirection = redirection->next;
	}
	return (i);
}

int	ft_n_redout(t_redir *redirection)
{
	int	i;

	i = 0;
	while (redirection)
	{
		if (ft_strcmp(redirection->op, ">") == 0)
			i++;
		if (ft_strcmp(redirection->op, ">>") == 0)
			i++;
		redirection = redirection->next;
	}
	return (i);
}

void	ft_single_hdoc(t_bp *bp)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		ft_put_syserr_exit(bp, "Minichelita");
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, hdoc_ctrl_c_single);
		if (ft_exec_redir(bp, bp->commands_lst[bp->n].redirection) != 0)
			ft_put_syserr(bp, "Minichelita");
		ft_exit_free(bp);
	}
	else
	{
		while (waitpid(-1, &status, 0) != -1 && errno != ECHILD)
		{
			if (WIFEXITED(status))
				bp->exit_status = WEXITSTATUS(status);
		}
	}
}
