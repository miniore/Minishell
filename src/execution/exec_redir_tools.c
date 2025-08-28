/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:37:39 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/26 19:51:27 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fr_input_handler(t_redir *redirection, int pipe_fd)
{
	char	*input;

	signal(SIGINT, hdoc_ctrl_c);
	input = readline(">");
	if (!input)
	{
		if (!input && g_exit_status != 130)
			ft_putstr_fd("warning: here-document delimited by EOF\n", 2);
		//ft_putnbr_fd((int)g_exit_status, 2);
		free(input);
		return (EXIT_FAILURE);
	}
	if (ft_strcmp(input, redirection->del) == 0)
	{
		free(input);
		return (EXIT_FAILURE);
	}
	write(pipe_fd, input, ft_strlen(input));
	write(pipe_fd, "\n", 1);
	free(input);
	return (EXIT_SUCCESS);
}

int	ft_lst_rdo(t_redir *redirection)
{
	t_redir	*iter;

	iter = redirection->next;
	while (iter)
	{
		if (ft_strcmp(iter->op, "<") == 0)
			return (1);
		if (ft_strcmp(iter->op, "<<") == 0)
			return (1);
		iter = iter->next;
	}
	return (0);
}
