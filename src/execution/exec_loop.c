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

void exec_singels(t_backpack *backpack, char **envp, t_env *path);
void exec_pipes(t_backpack *backpack, char **envp, t_env *path);
int is_buidins(t_backpack *backpack);

void	exit_error(void)
{
	perror("Minichelita");
	exit(EXIT_FAILURE);
}

int exec_loop(t_backpack *backpack, char **envp)
{
    t_env *path;

    path = search_node(&backpack->env, "PATH");
    backpack->n = 0;
    if (backpack->commands_nb == 1)
        exec_singels(backpack, envp, path);    
    else
        exec_pipes(backpack, envp, path);
    g_exit_status = 0;
    return(1);
}

void exec_pipes(t_backpack *backpack, char **envp, t_env *path)
{
    int pipe_fd[2];
    int prev_fd = -1;
    pid_t pid;
    int status;

    backpack->n = 0;
    while (backpack->n < (int)backpack->commands_nb)
    {
        if (backpack->n < (int)backpack->commands_nb - 1)
        {
            if (pipe(pipe_fd) == -1)
                exit_error();
        }
        pid = fork();
        if (pid == -1)
            exit_error();
        else if (pid == 0)
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (backpack->n < (int)backpack->commands_nb - 1)
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }
            ft_exec_redir(backpack->commands_lst[backpack->n].redirection);
            executor(backpack, envp, path);
            exit(0);
        }
        else
        {
            waitpid(pid, &status, 0);
            if (prev_fd != -1)
                close(prev_fd);
            if (backpack->n < (int)backpack->commands_nb - 1)
            {
                close(pipe_fd[1]);
                prev_fd = pipe_fd[0];
            }
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

void exec_singels(t_backpack *backpack, char **envp, t_env *path)
{
    pid_t	p_id;
    int	status;

    backpack->n = 0;
    if (backpack->commands_lst[0].command != NULL)
    {
        if (is_buidins(backpack) == 1)
        {
            if(!backpack->commands_lst[backpack->n].redirection)
                executor(backpack, envp, path);
            else
            {
                p_id = fork();//Cuando es un solo comando cambia fd en el proceso padre, la entrada de la shell pasa al archivo
                if (p_id == 0)
                {
                    ft_exec_redir(backpack->commands_lst[backpack->n].redirection);
                    executor(backpack, envp, path);
                    exit(0);
                }
                waitpid(p_id, &status, 0);
            }
        }
        else
        {
            p_id = fork();
            if (p_id == -1)
		        exit_error();
            else if (p_id == 0)
            {
                ft_exec_redir(backpack->commands_lst[backpack->n].redirection);
                run_cmd(process_tok(&backpack->commands_lst[backpack->n]), path, envp);          
            }
            waitpid(p_id, &status, 0);
        }
    }
}
