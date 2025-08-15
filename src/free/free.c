/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:12:31 by miniore           #+#    #+#             */
/*   Updated: 2025/08/15 18:42:03 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_redirections(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->op);
		free(redir->del);
		free(redir);
		redir = tmp;
	}
}

void	free_arguments(t_list *args)
{
	t_list	*tmp;

	while (args)
	{
		tmp = args->next;
		free(args->content);
		free(args);
		args = tmp;
	}
}

void	free_command_list(tok_lst *commands_lst, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (commands_lst[i].command)
			free(commands_lst[i].command);
		if (commands_lst[i].arguments)
			free_arguments(commands_lst[i].arguments);
		if (commands_lst[i].redirection)
			free_redirections(commands_lst[i].redirection);
		i++;
	}
	if (size > 0)
	{
		free(commands_lst);
		commands_lst = NULL;
	}
}
