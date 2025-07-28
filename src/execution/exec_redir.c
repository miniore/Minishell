/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:05:27 by miniore           #+#    #+#             */
/*   Updated: 2025/07/28 18:56:43 by porellan         ###   ########.fr       */
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

static void	ft_redir_heredoc(t_redir *redirection) //AÑADIR GESTION DE CTRL+C Y CTRL+D!!!!!
{
    int pipe_fd[2];
	char *input;

	if (pipe(pipe_fd) == -1)
        exit_error();
    while(1)
    {
        input = readline(">");
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
