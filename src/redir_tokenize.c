/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:46:20 by porellan          #+#    #+#             */
/*   Updated: 2025/06/12 14:59:13 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_add_last(t_redir **lst, t_redir *new)
{
	t_redir	*act;

	if (!*lst)
		*lst = new;
	else
	{
		act = *lst;
		while (act->next != NULL)
			act = act->next;
		act->next = new;
        new->prev = act;
	}
}

t_redir *new_redir_node(char *token)
{
    t_redir *node;

    node = (t_env *) malloc (sizeof(t_env));
    if (!node)
        return (NULL);
    node->var = var;
    node->content = content;
    node->prev = NULL;
    node->next = NULL;
    return (node);
}

void    ft_redirections(t_backpack *backpack, char *command)
{
    while(!ft_is_redirct(command[backpack->len + 1]))
        backpack->len++;
    if(backpack->len - backpack->i > 1 || (backpack->len - backpack-> i == 1 &&
            command[backpack->len - 1] != command[backpack->len]))
    {
        printf("bash: syntax error near redirection token.");
        return;
    }
    backpack->token = ft_substr(command, backpack->i, backpack->len - backpack->i);
    backpack->commands_lst[backpack->n].redirection.op = backpack->token;
    backpack->i = (int)backpack->len;
}
