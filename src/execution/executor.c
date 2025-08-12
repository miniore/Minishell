/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:43:18 by frlorenz          #+#    #+#             */
/*   Updated: 2025/07/30 21:00:30 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void executor(t_backpack *backpack, char **envp, t_env *path)
{
    if (!backpack->commands_lst[backpack->n].command)
        return ;
    if (ft_strcmp(backpack->commands_lst[backpack->n].command, "pwd")  == 0)
        pwd(backpack);
    else if(ft_strcmp(backpack->commands_lst[backpack->n].command, "echo")  == 0)
        ft_echo(backpack->commands_lst[backpack->n].arguments);
    else if(ft_strcmp(backpack->commands_lst[backpack->n].command, "cd")  == 0)
        cd(backpack->commands_lst[backpack->n].arguments, backpack->env);
    else if(ft_strcmp(backpack->commands_lst[backpack->n].command, "exit")  == 0)
        ft_exit(backpack); // habria que mirar de liberar.......
    else if(ft_strcmp(backpack->commands_lst[backpack->n].command, "env")  == 0)
        ft_env(backpack, 1);
    else if(ft_strcmp(backpack->commands_lst[backpack->n].command, "export")  == 0)
        ft_export(backpack);
    else if(ft_strcmp(backpack->commands_lst[backpack->n].command, "unset")  == 0)
        ft_unset(backpack);
    else
        run_cmd(process_tok(&backpack->commands_lst[backpack->n]), path, envp);
}
