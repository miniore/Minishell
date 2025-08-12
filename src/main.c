/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:40:48 by miniore           #+#    #+#             */
/*   Updated: 2025/08/04 20:20:12 by frlorenz         ###   ########.fr       */
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

int main(int argc, char **argv, char **envp)
{
    t_backpack  *backpack;
    char    *input;
    
    (void)argv;
    //printf con unas macros que indican el archivo y la linea desde donde se a ejecutado para DEBUGEAR!!!!!!!
    //printf("||((%s En_Linea %d))||=> %s\n", __FILE__, __LINE__, "HOLA ¿¿QUIZAS SOY UN ERROR?? ¿¿O NO??");
    if(argc != 1)
		return(EXIT_FAILURE);
    backpack = (t_backpack *)ft_calloc(1, sizeof(t_backpack));
    if(!backpack)
    {
        ft_put_pererr(backpack, "Minichelita: malloc error.\n", 1);
        return(EXIT_FAILURE);
    }
    fill_env(&backpack->env, envp);
	while(1)
    {
        signal(SIGINT, handle_ctrl_c);
        // if (g_exit_status == SIGINT || g_exit_status == SIGQUIT)
	    //     write(1, "\r", 1);
        input = readline("Minichelita> ");
        if(g_exit_status == 130)
            backpack->exit_status = g_exit_status;
        printf("%i\n",g_exit_status);
        if(!input)
        {
            g_exit_status = 131;
            backpack->exit_status = g_exit_status;
            backpack->commands_nb = 0;
            break;
        }
        g_exit_status = 0;
        if(ft_void_input(input))
        {
            free(input);
            continue;
        }
        add_history(input);
        if(ft_get_command(backpack, input))
        {
            ft_cmd_free(backpack);
            free(input);
            continue;
        }
        exec_loop(backpack, envp);   //else??
        ft_cmd_free(backpack);
        free(input);
    }
    printf("Nos vamos. Saliendo.\n");
    ft_exit_free(backpack);
    rl_clear_history();
    return(EXIT_SUCCESS);
}
// int main(int argc, char **argv, char **envp)
// {
//     t_backpack  *backpack;
//     char    *input;

//     (void)argv;
//     (void)envp;
//     if (argc != 1)
//         return (EXIT_FAILURE);

//     backpack = (t_backpack *)ft_calloc(1, sizeof(t_backpack));
//     fill_env(&backpack->env, envp);

//     while (1)
//     {
//         signal(SIGINT, handle_ctrl_c);
//         input = readline("Minichelita> ");

//         if (ft_catch_exit_signal(input))
//         {
//             free(input);
//             ft_exit_free(backpack);
//             rl_clear_history();
//             return (EXIT_SUCCESS);
//         }

//         if (ft_void_input(input))
//         {
//             free(input);
//             continue;
//         }

//         add_history(input);

//         if (ft_get_command(backpack, input))
//             printf("Syntax error.\n");

//         exec_loop(backpack, envp);
//         ft_cmd_free(backpack);
//         free(input);
//     }
// }
