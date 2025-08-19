/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:49:11 by miniore           #+#    #+#             */
/*   Updated: 2025/08/15 21:18:32 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_commands_list(t_bp *bp)
{
    printf("\n=========== 🧠 LISTA DE COMANDOS ===========\n");

    for (size_t i = 0; i < bp->commands_nb; i++)
    {
        t_tok_lst *cmd = &bp->commands_lst[i];
        printf("\n🔹 **Comando %zu**\n", i + 1);
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

    printf("Total de comandos: %zu\n", bp->commands_nb);
    printf("=============================================\n");
}

static void	ft_tokenize(t_bp *bp, char *command)
{
	bp->cmd_flag = 0;
	bp->len = 0;
	ft_extract_tokens(bp, command);
}

static size_t	ft_ignore_quotes(char *input, size_t len)
{
	while (input[len] != '|' && input[len] != '\0')
	{
		if (!ft_is_quotes(input[len]) || !ft_is_dquotes(input[len]))
			len = ft_ignore_qargs(input, len);
		len++;
	}
	return (len);
}

static void	ft_extract_commands(t_bp *bp, char *input, char **commands)
{
	size_t	len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = 0;
	while (input[len] != '\0')
	{
		if (input[i] == '|' && input[i + 1] == '|')
			break ;
		len = ft_ignore_quotes(input, len);
		if (i != 0)
			i++;
		commands[j] = ft_substr(input, i, len - i);
		ft_tokenize(bp, commands[j]);
		i = (int)len;
		if (input[len] == '|')
			len++;
		j++;
		bp->n++;
	}
	print_commands_list(bp);
}

static size_t	ft_count_commands(char *input)
{
	size_t	i;
	size_t	commands_nb;

	i = 0;
	commands_nb = 1;
	while (input[i] != '\0')
	{
		if (!ft_is_quotes(input[i]))
			i = ft_ignore_qargs(input, i);
		if (!ft_is_dquotes(input[i]))
			i = ft_ignore_qargs(input, i);
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
				return (commands_nb);
			commands_nb++;
		}
		if (input[i] == '\0')
			return (commands_nb);
		i++;
	}
	return (commands_nb);
}

int	ft_get_command(t_bp *bp, char *input)
{
	char	**commands;

	bp->err_flag = 0;
	bp->n = 0;
	if (ft_syntax_parse(bp, input))
		return (EXIT_FAILURE);
	bp->commands_nb = ft_count_commands(input);
	commands = (char **)ft_calloc(bp->commands_nb + 1, sizeof(char *));
	if (!commands)
	{
		ft_put_pererr(bp, "Minichelita: malloc error.\n", 1);
		return (EXIT_FAILURE);
	}
	bp->commands_lst = (t_tok_lst *)ft_calloc(bp->commands_nb, sizeof(t_tok_lst));
	if (!bp->commands_lst)
	{
		ft_put_pererr(bp, "Minichelita: malloc error.\n", 1);
		return (EXIT_FAILURE);
	}
	ft_extract_commands(bp, input, commands);
	free_array(commands);
	return (EXIT_SUCCESS);
}
