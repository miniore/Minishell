/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:40:48 by miniore           #+#    #+#             */
/*   Updated: 2025/08/15 16:13:54 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_exit_status = 0;

static int  ft_void_input(char *input)
{
    int     i;

    if (*input == '\0')
        return(EXIT_FAILURE);
    i = 0;
    while(input[i] == 32)
        i++;
    if(input[i] == '\0')
        return(EXIT_FAILURE);
    return(EXIT_SUCCESS);
}

static t_backpack *ft_backpack_creator(t_backpack *backpack)
{
    backpack = (t_backpack *)ft_calloc(1, sizeof(t_backpack));
    if(!backpack)
        ft_put_pererr(backpack, "Minichelita: malloc error.\n", 1);
    return(backpack);
}

static int  ft_input_loop(t_backpack *backpack, char *input)
{
    if(g_exit_status == 130)
        backpack->exit_status = g_exit_status;
    if(!input)
    {
        g_exit_status = 131;
        backpack->commands_nb = 0;
        printf("Nos vamos. Saliendo.\n");
        ft_exit_free(backpack);
        exit(g_exit_status);
    }
    g_exit_status = 0;
    if(ft_void_input(input))
    {
        free(input);
        return(EXIT_FAILURE);
    }
    add_history(input);
    if(ft_get_command(backpack, input))
    {
        if(backpack->exit_status != 258)
            ft_cmd_free(backpack);
        free(input);
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
    t_backpack  *backpack;
    char    *input;
    
    (void)argv;
    backpack = NULL;
    if(argc != 1)
		return(EXIT_FAILURE);
    backpack = ft_backpack_creator(backpack);
    if(!backpack)
        return(EXIT_FAILURE);
    fill_env(&backpack->env, envp);
	while(1)
    {
        signal(SIGQUIT, SIG_DFL);
        signal(SIGINT, handle_ctrl_c);
        input = readline("Minichelita> ");
        if(ft_input_loop(backpack, input))
            continue;
        exec_loop(backpack, envp);
        ft_cmd_free(backpack);
        free(input);
    }
    ft_exit_free(backpack);
    rl_clear_history();
    return(EXIT_SUCCESS);
}
