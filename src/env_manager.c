/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:59:44 by frlorenz          #+#    #+#             */
/*   Updated: 2025/05/13 17:50:31 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct t_env new_node(char *var, char *cont);
char *cut_str(char *str, bool check);

struct t_env *new_node(char *var)
{
    t_env *node;

    node = (t_env *) malloc (size_of (t_env));
    if (!node)
        return(0);
    node->var = cut_str(var, TRUE);
    node->content = cut_str(var, FALSE);
    node->write = TRUE;
    node->next = NULL;
    return (node);
}

char *cut_str(char *str, bool check)
{
    char *temp;
    int i;
    
    if (check)
    {
        i = 0;
        while (str[i] != '=')
        {
            temp[i] = str[i];
            i++;
        }
        return(temp);
    }
    else
    {
        while (str[i] != '=')
            i++;
        i++;
        while (str[i] != '\0')
        {
            temp[i] = str[i];
            i++;
        }
        return(temp);
    }
}

bool fill_env(struct t_env **stack, cha **envp)
{
    t_env *node;
    int i;

    i = 0;
    while(envp[i] != '\0')
    {
        node = new_node(envp[i]);   
        if (!node)
        {
            free(stack); //hay que liberar el stack entero..........
            return (FALSE);
        }
        attach_node(stack, node);
        i++;
    }
    return(TRUE);
}

struct t_env	*last_node(struct t_env *stack)
{
	int	i;
	int	j;

	i = 0;
	while (stack != NULL)
	{
		stack = stack->next;
		i++;
	}
	j = 0;
	while (j < i - 1)
	{
		stack = stack->next;
		j++;
	}
	return (stack);
}
void	attach_node(struct t_env **stack, t_env *new)
{
	t_env	*last;

	last = *stack;
	if (last == NULL)
        *stack = new;
	else
	{
		last = last_node(*stack);
		last->next = new;
	}
}
