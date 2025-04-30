/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:43:18 by frlorenz          #+#    #+#             */
/*   Updated: 2025/04/30 11:59:23 by frlorenz         ###   ########.fr       */
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
        echo(com_tokens->arguments);
    }
}
