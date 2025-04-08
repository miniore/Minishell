/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:12:31 by miniore           #+#    #+#             */
/*   Updated: 2025/03/27 12:20:12 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void free_list(t_list *commands_lst)
{
    t_list *temp;
    tok_lst *cmd;

    while (commands_lst)
    {
        temp = commands_lst;
        cmd = (tok_lst *)commands_lst->content;
        free(cmd->command);
		if(cmd->arguments)
			ft_lstclear(&cmd->arguments, free);
		if(cmd->redirection)
			ft_lstclear(&cmd->redirection, free);
        free(cmd->option);
        free(cmd);
        commands_lst = commands_lst->next;
        free(temp);
    }
}
