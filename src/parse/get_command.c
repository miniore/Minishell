/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:49:11 by miniore           #+#    #+#             */
/*   Updated: 2025/08/21 21:39:57 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	bp->commands_lst = (t_tok_l *)ft_calloc(bp->commands_nb, sizeof(t_tok_l));
	if (!bp->commands_lst)
	{
		ft_put_pererr(bp, "Minichelita: malloc error.\n", 1);
		return (EXIT_FAILURE);
	}
	ft_extract_commands(bp, input, commands);
	free_array(commands);
	return (EXIT_SUCCESS);
}
