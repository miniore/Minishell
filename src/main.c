/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:40:48 by miniore           #+#    #+#             */
/*   Updated: 2025/06/11 18:06:24 by frlorenz         ###   ########.fr       */
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
        free(input);
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
    t_backpack  *backpack;
    char    *input;
    
    (void)argv;
    (void)envp;
    //printf con unas macros que indican el archivo y la linea desde donde se a ejecutado para DEBUGEAR!!!!!!!
    printf("||((%s En_Linea %d))||=> %s\n", __FILE__, __LINE__, "HOLA ¿¿QUIZAS SOY UN ERROR?? ¿¿O NO??");
    backpack = (t_backpack *)ft_calloc(1, sizeof(t_backpack));     //Mirar si es necesario reservar memoria para backpack
    if(argc != 1)
		return(EXIT_FAILURE);
    fill_env(&backpack->env, envp);  //Detectado segfault aquí!!!1
	while(1)
    {
        signal(SIGINT, handle_ctrl_c);
        input = readline("Minichelita> ");
        if(ft_catch_exit_signal(input))
            break;
        if(ft_void_input(input))
        {
            free(input);
            continue;
        }
        add_history(input);                 // Arreglar uso del historial si usas ctrl+c en un comando ya usado. Se guarda para la siguiente ejecucion¿?
        if(ft_get_command(backpack, input))
            printf("Syntax error.\n");
        exec_loop(backpack, envp);
        //executor(backpack, envp); // Funcion a la que le pasamos la lista de los comandos y que las cosas se intenten ejecutar.
        //free_list(comandos, demomento); //MIRAR SEGFAULT CUANDO VARIABLES EXPANDIBLES
        free(input);            //Readline genera malloc para la entrada. En caso de liberarlas no es necesario usar clear_history¿?
    }
    return(EXIT_SUCCESS);
}
