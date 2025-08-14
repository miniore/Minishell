/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:05:27 by miniore           #+#    #+#             */
/*   Updated: 2025/08/14 19:10:19 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_lst_rdo(t_redir *redirection)
{
    t_redir *iter;
    
    iter = redirection->next; // le pasamos el siguiente nodo a iter
    while(iter) //si iter fuera NULL no entraria
    {
        if(ft_strcmp(iter->op, "<")  == 0) //comprobamos si iter-> es <
            return (1);//si lo es devolvemos 1 indicando que redirection no es la ultima redireccion de entrada
        if(ft_strcmp(iter->op, "<<")  == 0)// lo mismo con los Hdocs
            return (1);
        iter = iter->next;
    }
    return (0);
}

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

static int	ft_redir_in(t_redir *redirection)
{
    int fd;

    fd = open(redirection->del, O_RDONLY);
    if(fd == -1)
        return (EXIT_FAILURE);    //modificar con perror???
    if (ft_lst_rdo(redirection) == 0)
    {
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    else
        close(fd);
    return (EXIT_SUCCESS);
}

static void	ft_redir_heredoc(t_redir *redirection, int exec)
{
    int pipe_fd[2];
    int dup_fd;
    char buffer[102400];
    size_t bytes_read;
	char *input;

	if (pipe(pipe_fd) == -1)
        exit_error();  //cambiarrrrr!!!!!
    rl_clear_history();
    dup_fd = dup(STDIN_FILENO);
    while(g_exit_status != 130)
    {
        signal(SIGINT, hdoc_ctrl_c);
        input = readline(">");
        if(!input)
        {
            if(!input && g_exit_status != 130)
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
    if(g_exit_status == 130 && exec == 1)
    {
        write(pipe_fd[1], " ", 1);
        bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
    }
    close(pipe_fd[1]);
    if (exec == 1)
        dup2(pipe_fd[0], STDIN_FILENO);
    if(g_exit_status == 130 && exec == 0)
        dup2(dup_fd, STDIN_FILENO);
    close(pipe_fd[0]);
    close(dup_fd);
}

static void ft_exec_hdoc(t_redir *redirection)
{
    t_redir *iter;
    int i;
    int j;
    
    i = 0;
    j = 1;
    iter = redirection;
    while(iter)
    {
        if(ft_strcmp(iter->op, "<<")  == 0)
            i++;
        iter = iter->next;  
    }
    while(redirection)
    {
        if(ft_strcmp(redirection->op, "<<")  == 0)
        {
            if (j == i)
                ft_redir_heredoc(redirection, 1);
            else
                ft_redir_heredoc(redirection, 0);
            j++;
        }
        redirection = redirection->next;  
    }
}


int    ft_exec_redir(t_redir *redirection)
{
    ft_exec_hdoc(redirection);
    while(redirection)
    {
        if(ft_strcmp(redirection->op, "<")  == 0)
        {
			if(ft_redir_in(redirection))
                return (EXIT_FAILURE);
        }
        if(ft_strcmp(redirection->op, ">")  == 0)
			ft_redir_out(redirection, 0);
        if(ft_strcmp(redirection->op, ">>")  == 0)
			ft_redir_out(redirection, 1);
        redirection = redirection->next;
    }
    return (EXIT_SUCCESS);
}
