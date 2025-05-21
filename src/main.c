/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:40:48 by miniore           #+#    #+#             */
/*   Updated: 2025/05/20 19:25:48 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_ctrl_c(int sig)
{
    (void)sig;
    printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

static int ft_catch_exit_signal(char *input)
{
    signal(SIGQUIT, SIG_IGN);
    if(!input)
    {
        printf("Nos vamos. Saliendo.\n");
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}
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

int main(int argc, char **argv, char **envp)
{
    t_env   *env;
    
    (void)argv;
    env = NULL;
    if(argc != 1)
		return(EXIT_FAILURE);
    fill_env(&env, envp); //
	while(1)
    {
        char    *input;

        signal(SIGINT, handle_ctrl_c);
        input = readline("Minichelita> ");
        if(ft_catch_exit_signal(input))
        {
            free(input);
            break;
        }
        if(ft_void_input(input))
        {
            free(input);
            continue;
        }
        add_history(input);                 // Arreglar uso del historial si usas ctrl+c en un comando ya usado. Se guarda para la siguiente ejecucion¿?
        if(ft_get_command(input, &env))
            printf("Syntax error.\n");
        free(input);            //Readline genera malloc para la entrada. En caso de liberarlas no es necesario usar clear_history¿?
    }
    return(EXIT_SUCCESS);
}
