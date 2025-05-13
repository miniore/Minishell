/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:43:18 by frlorenz          #+#    #+#             */
/*   Updated: 2025/05/05 16:32:09 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void executor(tok_lst *com_tokens)
{
    if (ft_strncmp(com_tokens->command, "pwd", 3)  == 0)
    {
        if(com_tokens->arguments == NULL)
            pwd();
        else
            perror("pwd: too many arguments"); // Esto del los errores hay que mirarlo.
    }
    else if(ft_strncmp(com_tokens->command, "echo", 4)  == 0)
    {
        ft_echo(com_tokens->arguments);
    }
    else if(ft_strncmp(com_tokens->command, "cd", 2)  == 0)
    {
        cd(com_tokens->arguments);
    }
    else if(ft_strncmp(com_tokens->command, "exit", 4)  == 0)
    {
        exit(EXIT_SUCCESS); // habria que mirar de liberar.......
    }
}
