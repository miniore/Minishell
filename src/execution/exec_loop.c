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

void	exit_error(void)
{
	perror("ERROR");
	exit(EXIT_FAILURE);
}

int exec_loop(t_backpack *backpack, char **envp)
{
    int i;
    int j;
    pid_t	p_id;
    int	status;

    status = 0;
    i = backpack->commands_nb;
    j = 1;
    p_id = 0;
    while(j <= i)
    {
        p_id = fork();
        if (p_id == -1)
		    exit_error();
	    else if (p_id == 0)
		    executor(backpack, envp);
       //printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR"); 
       backpack->commands_lst++; //ESTO PUEDE FALLAR SEGURAMENTE !!!!!!!!!!
       j++;
       waitpid(p_id, &status, 0);
    }
    
    return(1);
}

