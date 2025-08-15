/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:43:18 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/15 19:35:43 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_bp *bp, char **envp, t_env *path)
{
	if (!bp->commands_lst[bp->n].command)
		return ;
	if (ft_strcmp(bp->commands_lst[bp->n].command, "pwd") == 0)
		pwd(bp);
	else if (ft_strcmp(bp->commands_lst[bp->n].command, "echo") == 0)
		ft_echo(bp->commands_lst[bp->n].arguments);
	else if (ft_strcmp(bp->commands_lst[bp->n].command, "cd") == 0)
		cd(bp);
	else if (ft_strcmp(bp->commands_lst[bp->n].command, "exit") == 0)
		ft_exit(bp);
	else if (ft_strcmp(bp->commands_lst[bp->n].command, "env") == 0)
		ft_env(bp, 1);
	else if (ft_strcmp(bp->commands_lst[bp->n].command, "export") == 0)
		ft_export(bp);
	else if (ft_strcmp(bp->commands_lst[bp->n].command, "unset") == 0)
		ft_unset(bp);
	else
		process_tok(bp, path, envp);
}
