/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:43:18 by frlorenz          #+#    #+#             */
/*   Updated: 2025/06/03 12:41:33 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void executor(t_backpack *backpack)
{
    //t_env *act;
    
    //act = NULL;
    backpack->n = 0;
    //  Utilizar strleen para arreglar comparaciones
    if (ft_strncmp(backpack->commands_lst[backpack->n].command, "pwd", 3)  == 0)
    {
        if(backpack->commands_lst[backpack->n].arguments == NULL)
            pwd();
        else
            perror("pwd: too many arguments"); // Esto del los errores hay que mirarlo.
    }
    else if(ft_strncmp(backpack->commands_lst[backpack->n].command, "echo", 4)  == 0)
    {
        ft_echo(backpack->commands_lst[backpack->n].arguments);
    }
    else if(ft_strncmp(backpack->commands_lst[backpack->n].command, "cd", 2)  == 0)
    {
        cd(backpack->commands_lst[backpack->n].arguments);
    }
    else if(ft_strncmp(backpack->commands_lst[backpack->n].command, "exit", 4)  == 0)
    {
        exit(EXIT_SUCCESS); // habria que mirar de liberar.......
    }
    else if(ft_strncmp(backpack->commands_lst[backpack->n].command, "env", 3)  == 0)
    {
        ft_env(&backpack->env);
    }
    else if(ft_strncmp(backpack->commands_lst[backpack->n].command, "export", 6)  == 0)
    {
        ft_export(backpack);
    }
    else if(ft_strncmp(backpack->commands_lst[backpack->n].command, "unset", 5)  == 0)
    {
        ft_unset(backpack);
    }
}
