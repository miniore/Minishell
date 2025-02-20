/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:40:48 by miniore           #+#    #+#             */
/*   Updated: 2025/02/20 17:16:09 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int main(void)
{
    while(1)
    {
        char    *input;
        int     i;

        signal(SIGINT, handle_ctrl_c);
        signal(SIGQUIT, SIG_IGN);
        input = readline("Minichelita> ");
        if(!input || !strcmp(input, "exit"))
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
        //ft_tok_com(input);
        if(ft_valid_com(input))        //Parsear y tokenizar la entrada para detectar comandos
            printf("%s: No se encontró la orden.\n", input);
        free(input);            //Readline genera malloc para la entrada. En caso de liberarlas no es necesario usar clear_history¿?
    }
    return(EXIT_SUCCESS);
}
