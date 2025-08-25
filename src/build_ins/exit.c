/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:13:13 by porellan          #+#    #+#             */
/*   Updated: 2025/08/25 16:10:37 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < 47 || str[i] > 58)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_bp *bp)
{
	t_list	*temp;
	char	*aux;

	temp = bp->commands_lst[bp->n].arguments;
	while (temp)
	{
		aux = ft_strdup(temp->content);
		if (!ft_is_numeric(aux))
		{
			ft_put_pererr(bp, "Minichelita: exit: no numeric arg\n", 2);
			break ;
		}
		temp = temp->next;
		if (temp)
		{
			ft_put_pererr(bp, "Minichelita: exit: too many arguments\n", 1);
			free(aux);
			return ;
		}
		bp->exit_status = ft_atoi(aux);
	}
	ft_putstr_fd("Nos vamos. Saliendo.\n", 2);
	ft_exit_free(bp);
}
