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

int exec_loop(t_backpack *backpack, char **envp)
{
    int i;
    int j;

    i = backpack->commands_nb;
    j = 1;
    while(j <= i)
    {
       printf("%s\n", backpack->commands_lst->command);
       void run_cmd(process_tok(backpack->commands_lst), **envp)
       backpack->commands_lst++; //ESTO PUEDE FALLAR SEGURAMENTE !!!!!!!!!!
       j++;
    }
    return(1);
}

//Funcion que genera un array 2D con el comando y sus flags a partir de un tok_lst
//para poder pasarlo al execv mas adelante
char **process_tok(tok_lst *token)
{
    int i;
    char **cmd;

    i = ft_lstsize(token->arguments);
    cmd = (char **) ft_calloc(i + 2, sizeof (char **));
    if (!cmd)
        return(NULL);
    ft_memcpy(cmd[0], token->command, ft_strlen(token->command));
    while(token->arguments)
    {
        
        token->arguments++;
    }

    return(cmd);
}