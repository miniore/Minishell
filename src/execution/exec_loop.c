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

void exec_singels(t_backpack *backpack, char **envp);
void exec_pipes(t_backpack *backpack, char **envp);
int is_buidins(t_backpack *backpack);

void	exit_error(void)
{
	perror("ERROR");
	exit(EXIT_FAILURE);
}

int exec_loop(t_backpack *backpack, char **envp)
{
    //int i;
    //pid_t	p_id;
    //int fd[3];
    int	status;
   // pid_t comp;

    status = 0;
    backpack->n = 0;
    //fd[0] = STDIN_FILENO;
    if (backpack->commands_nb == 1)
        exec_singels(backpack, envp);
    else
        exec_pipes(backpack, envp);
    return(1);
}

void exec_pipes(t_backpack *backpack, char **envp)
{
    int i;
    pid_t	p_id;
    int fd[3];
    int	status;
    pid_t comp;

    i = backpack->commands_nb;
    status = 0;
    while(backpack->n < i)
        {
            if (pipe(&fd[1]) == -1)
            {
                close(fd[1]);
                close(fd[2]);
                //return(0);
            }
            p_id = fork();
            printf("((%s En_Linea %d P_id = %i))||=> %i\n", __FILE__,__LINE__, p_id, backpack->n);
            if (p_id == -1)
                exit_error();
            else if (p_id == 0) // Procesos Hijos
            {
                dup2(fd[2], STDOUT_FILENO);
                dup2(fd[1], STDIN_FILENO);
                //printf("((%s En_Linea %d P_id = %i fd[1] = %i))||\n", __FILE__,__LINE__, p_id, (int)fd[1]);
                //printf("((%s En_Linea %d P_id = %i fd[2] = %i))||\n", __FILE__,__LINE__, p_id, (int)fd[2]);  
                executor(backpack, envp);
                exit(0);    
            }
            else if (p_id > 0) // Proceso Padre
            {
                comp = waitpid(p_id, &status, 0);
                printf("TERMINO EL HIJO Nº => %i\n\n", comp);
            }
            backpack->n++;
        }
}

int is_buidins(t_backpack *backpack)
{
    if (ft_strcmp(backpack->commands_lst[backpack->n].command, "pwd")  == 0)
        return (1);
    else if(ft_strcmp(backpack->commands_lst[backpack->n].command, "echo")  == 0)
        return (1);
    else if(ft_strcmp(backpack->commands_lst[backpack->n].command, "cd")  == 0)
        return (1);
    else if(ft_strcmp(backpack->commands_lst[backpack->n].command, "exit")  == 0)
        return (1);
    else if(ft_strcmp(backpack->commands_lst[backpack->n].command, "env")  == 0)
        return (1);
    else if(ft_strcmp(backpack->commands_lst[backpack->n].command, "export")  == 0)
        return (1);
    else if(ft_strcmp(backpack->commands_lst[backpack->n].command, "unset")  == 0)
        return (1);
    return (0);
}

void exec_singels(t_backpack *backpack, char **envp)
{
    pid_t	p_id;
    int	status;

    backpack->n = 0;
    if (is_buidins(backpack) == 1)
        executor(backpack, envp);
    else
    {
        p_id = fork();
        if (p_id == -1)
		    exit_error();
        else if (p_id == 0)
            run_cmd(process_tok(&backpack->commands_lst[backpack->n]), envp);
        waitpid(p_id, &status, 0);
    }
}
