/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:04:42 by porellan          #+#    #+#             */
/*   Updated: 2025/08/15 20:19:04 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_var_content(char *str)
{
	char	*content;
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	i++;
	content = ft_substr(str, i, len);
	return (content);
}

static int	ft_valid_char(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	ft_save_var(t_bp *bp, t_list *actual, char *var)
{
	char	*content;

	content = ft_var_content(actual->content);
	if (!content)
		content = "";
	if (!search_node(&bp->env, var))
		env_add_last(&bp->env, new_node(var, content));
	else
		modify_node(search_node(&bp->env, var), NULL, content);
	free(var);
}

static void	ft_check_error(t_bp *bp, char *var)
{
	if ((!ft_isalpha(var[0]) && var[0] != '_') || ft_valid_char(var))
		free(var);
	ft_put_pererr(bp, "Minichelita: export: not a valid identifier.\n", 258);
}

void	ft_export(t_bp *bp)
{
	t_list	*actual;
	char	*var;

	bp->n = 0;
	actual = bp->commands_lst[bp->n].arguments;
	if (!bp->commands_lst[bp->n].arguments)
		ft_env(bp, 0);
	while (actual)
	{
		if (!ft_strchr(actual->content, '='))
		{
			actual = actual->next;
			continue ;
		}
		var = name_var(actual->content);
		if (!var || (!ft_isalpha(var[0]) && var[0] != '_')
			|| ft_valid_char(var))
		{
			ft_check_error(bp, var);
			actual = actual->next;
			continue ;
		}
		ft_save_var(bp, actual, var);
		actual = actual->next;
	}
}
