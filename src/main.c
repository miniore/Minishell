/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:40:48 by miniore           #+#    #+#             */
/*   Updated: 2025/07/28 18:59:57 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_exit_status = 0;

static void handle_ctrl_c(int sig)
{
    (void)sig;
    g_exit_status = 130; // SIGINT => 128 + 2
    printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

// static int ft_catch_exit_signal(char *input)
// {
//     //signal(SIGQUIT, SIG_IGN);
//     // if(!input)
//     // {
//         printf("Nos vamos. Saliendo.\n");
//         //free(input);
//         return(EXIT_FAILURE);
//     //}
//     return(EXIT_SUCCESS);
// }
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
    backpack = (t_backpack *)ft_calloc(1, sizeof(t_backpack));
    if(argc != 1)
		return(EXIT_FAILURE);
    fill_env(&backpack->env, envp);
	while(1)
    {
        backpack->exit_status = g_exit_status;
        signal(SIGINT, handle_ctrl_c);
        input = readline("Minichelita> ");
        if(!input)
        {
            backpack->commands_nb = 0;
            break;
        }
        if(ft_void_input(input))
        {
            free(input);
            continue;
        }
        add_history(input);
        if(ft_get_command(backpack, input))
            printf("Syntax error.\n");
        exec_loop(backpack, envp);
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
