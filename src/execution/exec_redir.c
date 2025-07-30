/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:05:27 by miniore           #+#    #+#             */
/*   Updated: 2025/07/30 22:18:49 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redir_out(t_redir *redirection, int flag)
{
    int fd;

	if(flag)
        fd = open(redirection->del, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
        fd = open(redirection->del, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

static void	ft_redir_in(t_redir *redirection)
{
    int fd;

    fd = open(redirection->del, O_RDONLY);
    if(fd == 0)
        return;
    dup2(fd, STDIN_FILENO);
    close(fd);
}

static void hdoc_ctrl_c(int sig)
{
    (void)sig;
    g_exit_status = 130; // SIGINT => 128 + 2
    rl_on_new_line();
    rl_replace_line("", 0);
    exit(0);
}

static void	ft_redir_heredoc(t_redir *redirection)
{
    int pipe_fd[2];
	char *input;

	if (pipe(pipe_fd) == -1)
        exit_error();
    rl_clear_history();
    while(1)
    {
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, hdoc_ctrl_c);
        input = readline(">");
        if(!input)
        {
            ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `out')\n", 2);
            free(input);
            break;
        }  
        if(ft_strcmp(input, redirection->del) == 0)
        {
            free(input);
            break;
        }
        write(pipe_fd[1], input, ft_strlen(input));
        write(pipe_fd[1], "\n", 1);
        free(input);
    }
    close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
}

void    ft_exec_redir(t_redir *redirection)
{

    while(redirection)
    {
        if(ft_strcmp(redirection->op, ">")  == 0)
			ft_redir_out(redirection, 0);
        if(ft_strcmp(redirection->op, ">>")  == 0)
			ft_redir_out(redirection, 1);
        if(ft_strcmp(redirection->op, "<")  == 0)
			ft_redir_in(redirection);
        if(ft_strcmp(redirection->op, "<<")  == 0)
			ft_redir_heredoc(redirection);
        redirection = redirection->next;
    }
}
