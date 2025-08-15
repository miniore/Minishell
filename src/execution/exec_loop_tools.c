/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:11:56 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/15 17:21:41 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cmond_singel(t_backpack *backpack, char **envp, t_env *path)
{
    signal(SIGINT, handle_ctrl_c);
    if(!backpack->commands_lst[backpack->n].redirection)
        process_tok(backpack, path, envp);
    else
    {
        if (ft_exec_redir(backpack, backpack->commands_lst[backpack->n].redirection) != 0)
        {
            ft_put_syserr(backpack, "Minichelita");
            ft_exit_free(backpack);
        }
        else
            process_tok(backpack, path, envp);
    }
}

void ft_bin_singel(t_backpack *backpack, char **envp, t_env *path)
{
    pid_t	p_id;
    int	status;
    
    if(!backpack->commands_lst[backpack->n].redirection)
        executor(backpack, envp, path);
    else
    {
        signal(SIGQUIT, SIG_DFL);
        signal(SIGINT, SIG_IGN);
        p_id = fork();
        if (p_id == 0)
        {
            signal(SIGINT, handle_ctrl_c);
            if (ft_exec_redir(backpack, backpack->commands_lst[backpack->n].redirection) != 0)
                ft_put_syserr(backpack, "Minichelita");
            else
                executor(backpack, envp, path);
            ft_exit_free(backpack);
        }
        waitpid(p_id, &status, 0);
    }
}

static void ft_com_last_hdocs(t_backpack *backpack, int prev_fd)
{
    if(ft_n_hdocs(backpack->commands_lst[backpack->n].redirection) == 0)
    {
        if (prev_fd != -1)
        {
            dup2(prev_fd, STDIN_FILENO);
            close(prev_fd);
        }
    }
    else if (prev_fd != -1)
        close(prev_fd);
}

static void ft_pipe_redir(t_backpack *backpack, int prev_fd, int *pipe_fd)
{
    ft_com_last_hdocs(backpack, prev_fd);
    if (ft_exec_redir(backpack, backpack->commands_lst[backpack->n].redirection) != 0)
    {
        ft_put_syserr(backpack, "Minichelita");
        if (backpack->n < (int)backpack->commands_nb - 1)
        {
            close(pipe_fd[0]);
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[1]);
        }
        ft_exit_free(backpack);
    }
    if (ft_n_redout(backpack->commands_lst[backpack->n].redirection) == 0)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
    }
    else
    {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }
}

void ft_pipe_son(t_backpack *backpack, int prev_fd, int *pipe_fd, char **envp, t_env *path)
{
    signal(SIGINT, handle_ctrl_c);
    if(!backpack->commands_lst[backpack->n].redirection)
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
    }
    else
        ft_pipe_redir(backpack, prev_fd, pipe_fd);
    executor(backpack, envp, path);
    ft_exit_free(backpack);
}
