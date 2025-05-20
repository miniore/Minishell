/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:49:11 by miniore           #+#    #+#             */
/*   Updated: 2025/05/20 19:36:30 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_commands_list(t_list *command_list, t_env **env)
{
    t_list *cmd_node = command_list;  // Apunta al primer comando
    int cmd_index = 1;

    while (cmd_node)
    {
        tok_lst *cmd = (tok_lst *)cmd_node->content;  // Obtener el tok_lst del nodo
        printf("\n🔹 **Comando %d**\n", cmd_index++);
        printf("   🟢 Comando: %s\n", cmd->command);
        printf("   🔵 Opción: %s\n", cmd->option ? cmd->option : "(Ninguna)");

        // Imprimir argumentos
        printf("   🟠 Argumentos: ");
        t_list *arg_node = cmd->arguments;
        if (!arg_node)
            printf("(Ninguno)");
        else
        {
            while (arg_node)
            {
                printf("%s ", (char *)arg_node->content);
                arg_node = arg_node->next;
            }
        }
        printf("\n-----------------------\n");
        executor(cmd, env); // Funcion a la que le pasamos la lista de los comandos y que las cosas se intenten ejecutar.
        // Avanzar al siguiente comando en la lista
        cmd_node = cmd_node->next;

    }
}

static void ft_extract_commands(char *input, char **commands, t_env **env)
{
    t_list  *commands_lst;
    size_t  len;
    int     i;
    int     j;
    
    i = 0;
    j = 0;
    len = 0;
    commands_lst = NULL;
    while(input[len] != '\0')
    {
        while(input[len] != '|' && input[len] != '\0')
        {
            if(!ft_is_quotes(input[len]) || !ft_is_dquotes(input[len]))
                len = ft_ignore_qargs(input, len);
            len++;
        }
        if(i != 0)
            i++;
        commands[j] = ft_substr(input, i, len - i);
        printf("-----------------------\n");
        printf("Comando entero: %s\n", commands[j]);
        ft_tokenize(&commands_lst, commands[j]);
        i = (int)len;
        if(input[len] == '|')
            len++;
        j++;
    }
    print_commands_list(commands_lst, env);
    //free_list(commands_lst); //MIRAR SEGFAULT CUANDO VARIABLES EXPANDIBLES
}

static size_t ft_count_commands(char *input)
{
    size_t i;
    size_t commands_nb;
    
    i = 0;
    commands_nb = 1;
    while (input[i] != '\0')
    {
        if(!ft_is_quotes(input[i]))
            i = ft_ignore_qargs(input, i);
        if(!ft_is_dquotes(input[i]))
            i = ft_ignore_qargs(input, i);
        if (input[i] == '|')
            commands_nb++;
        if(input[i] == '\0')
            return(commands_nb); 
        i++;
    }
    return(commands_nb);
}

int ft_get_command(char *input, t_env **env)
{
    char **commands;
    size_t     commands_nb;

    if(ft_syntax_parse(input))
        return(EXIT_FAILURE);
    commands_nb = ft_count_commands(input);
    printf("Numero de comandos:%li\n", commands_nb);
    commands = (char **)ft_calloc(commands_nb + 1, sizeof(char *));
    if (!commands)
        return (EXIT_FAILURE);
    ft_extract_commands(input, commands, env);
    
    free_array(commands);
    return(EXIT_SUCCESS);
}
