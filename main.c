/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:40:48 by miniore           #+#    #+#             */
/*   Updated: 2025/02/27 13:23:07 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// int    ft_tok_com(char *input)
// {
//     if(ft_strtok(input))
//         return(EXIT_FAILURE);
// }

void handle_ctrl_c(int sig)
{
    (void)sig;
    printf("\n");
    rl_replace_line("", 0);               // Borra la línea actual
    rl_on_new_line();                     // Indica nueva línea
    rl_redisplay();
}

int main(int argc, char **argv, char **envp)
{
    if(argc != 1)
		return(EXIT_FAILURE);
    printf("%s\n", argv[1]);
    printf("%s\n", envp[1]);
	while(1)
    {
        char    *input;
        int     i;

        signal(SIGINT, handle_ctrl_c);
        signal(SIGQUIT, SIG_IGN);
        input = readline("Minichelita> ");
        if(!input)
        {
            printf("Nos vamos. Saliendo.\n");
            free(input);
            break;
        }
        if (*input == '\0')
        {
            free(input);
            continue;
        }
        i = 0;
        while(input[i] == 32)
            i++;
        if(input[i] == '\0')
        {
            free(input);
            continue;
        }
        add_history(input);                 // Arreglar uso del historial si usas ctrl+c en un comando ya usado. Se guarda para la siguiente ejecucion¿?
        ft_tokenize(input);        //Parsear y tokenizar la entrada para detectar comandos
        free(input);            //Readline genera malloc para la entrada. En caso de liberarlas no es necesario usar clear_history¿?
    }
    return(EXIT_SUCCESS);
}
