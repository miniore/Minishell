/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:21:44 by frlorenz          #+#    #+#             */
/*   Updated: 2025/06/04 17:02:35 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_add_last(t_env **lst, t_env *new)
{
	t_env	*act;

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

t_env *new_node(char *var, char *content)
{
    t_env *node;

    node = (t_env *) malloc (sizeof(t_env));
    if (!node)
        return (NULL);
    node->var = var;
    node->content = content;
    node->prev = NULL;
    node->next = NULL;
    return (node);
}

char **var_list(char **envp)
{
    char **lst;
    int i;

    i = 0;
    while(envp[i])
        i++;
    lst = (char **) ft_calloc(i + 1, sizeof (char **));
    if (!lst)
        return(NULL);
    i  = 0;
    while(envp[i])
    {  
        lst[i] = name_var(envp[i]);
        i++;
    }
    return(lst);
}

char *name_var(char *var)
{
    char *name;
    int i;
    
    i = 0;
    while(var[i] != '=')
        i++;
    if(i == 0)
        return(NULL);
    name = (char *) ft_calloc(i + 1, sizeof(char *));
    if (!name)
        return(NULL);
    i = 0;
    while(var[i] != '=')
    {
        name[i] = var[i];
        i++;
    }
    return(name); 
}

int ft_env(t_env **env)
{
    t_env *act;
    
    if(!env)
        return(0);
    else
    {
        printf("EYY\n");
        act = *env;
        while(act->next != NULL)
        {
            printf("%s = %s\n", act->var, act->content);
            act = act->next;
        }
        printf("%s = %s\n", act->var, act->content);
    }
    return (1);
}
