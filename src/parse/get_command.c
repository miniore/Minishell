/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:49:11 by miniore           #+#    #+#             */
/*   Updated: 2025/07/30 13:23:58 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_commands_list(t_backpack *backpack)
{
    printf("\n=========== 🧠 LISTA DE COMANDOS ===========\n");

    for (size_t i = 0; i < backpack->commands_nb; i++)
    {
        tok_lst *cmd = &backpack->commands_lst[i];
        printf("\n🔹 **Comando %zu**\n", i + 1);
        printf("   🟢 Comando: %s\n", (char *)cmd->command);
        printf("   🟢 Comando: %s\n", cmd->command ? cmd->command : "null");

        // Imprimir argumentos como lista
        printf("   🟠 Argumentos:\n");
        t_list *arg_node = cmd->arguments;
        int arg_index = 1;
        if (!arg_node)
        {
            printf("      - (Ninguno)\n");
        }
        else
        {
            while (arg_node)
            {
                printf("      %d. %s\n", arg_index++, (char *)arg_node->content);
                arg_node = arg_node->next;
            }
        }

        // Imprimir redirecciones como lista (nuevo modelo con t_redir)
        printf("   🔴 Redirecciones:\n");
        t_redir *redir_node = cmd->redirection;
        int redir_index = 1;
        if (!redir_node)
        {
            printf("      - (Ninguna)\n");
        }
        else
        {
            while (redir_node)
            {
                printf("      %d. Operador: %s, Target: %s\n", redir_index++,
                       redir_node->op ? redir_node->op : "(null)",
                       redir_node->del ? redir_node->del : "(null)");
                redir_node = redir_node->next;
            }
        }

        printf("---------------------------------------------\n");
    }

    printf("Total de comandos: %zu\n", backpack->commands_nb);
    printf("=============================================\n");
}

static int ft_tokenize(t_backpack *backpack, char *command)
{
    backpack->cmd_flag = 0;
    backpack->len = 0;
    ft_extract_tokens(backpack, command);
    return(EXIT_SUCCESS);
}

static void ft_extract_commands(t_backpack *backpack, char *input, char **commands)
{
    size_t  len;
    int     i;
    int     j;
    
    i = 0;
    j = 0;
    len = 0;
    while(input[len] != '\0')
    {
        if(input[i] == '|' && input[i + 1] == '|')
            break ;
        while(input[len] != '|' && input[len] != '\0')
        {
            if(!ft_is_quotes(input[len]) || !ft_is_dquotes(input[len]))
                len = ft_ignore_qargs(input, len);
            len++;
        }
        if(i != 0)
            i++;
        commands[j] = ft_substr(input, i, len - i);
        ft_tokenize(backpack, commands[j]);
        i = (int)len;
        if(input[len] == '|')
            len++;
        j++;
        backpack->n++;
    }
    print_commands_list(backpack);
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
        {
            if (input[i + 1] == '|')
                return(commands_nb);
            commands_nb++;
        }
        if(input[i] == '\0')
            return(commands_nb);
        i++;
    }
    return(commands_nb);
}

int ft_get_command(t_backpack *backpack, char *input)
{
    char **commands;

    if(ft_syntax_parse(backpack, input))
        return(EXIT_FAILURE);
    backpack->n = 0;
    backpack->commands_nb = ft_count_commands(input);
    commands = (char **)ft_calloc(backpack->commands_nb + 1, sizeof(char *));
    if (!commands)
    {
        ft_put_pererr(backpack, "Minichelita: malloc error.\n", 1);
        return (EXIT_FAILURE);
    }
    backpack->commands_lst = (tok_lst *)ft_calloc(backpack->commands_nb, sizeof(tok_lst));
    if (!backpack->commands_lst)
    {
        ft_put_pererr(backpack, "Minichelita: malloc error.\n", 1);
        return (EXIT_FAILURE);
    }
    ft_extract_commands(backpack, input, commands);
    free_array(commands);
    return(EXIT_SUCCESS);
}
