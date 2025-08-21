/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:22:22 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/21 21:35:39 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_flag(char *flag)
{
	int	i;

	i = 1;
	if (flag[i] == '\0')
		return (1);
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_echo_print(t_list *temp, bool opt)
{
	if (temp)
	{
		while (temp->next)
		{
			printf("%s ", (char *)temp->content);
			temp = temp->next;
		}
		printf("%s", (char *)temp->content);
		if (!opt)
			printf("\n");
	}
}

void	ft_echo(t_list *arg)
{
	t_list	*temp;
	bool	opt;

	temp = arg;
	opt = false;
	if (!arg)
		printf("\n");
	else
	{
		while (temp)
		{
			if (((char *)temp->content)[0] == '-')
			{
				if (!ft_check_flag((char *)temp->content))
					opt = true;
				else
					break ;
			}
			else
				break ;
			temp = temp->next;
		}
		ft_echo_print(temp, opt);
	}
}
