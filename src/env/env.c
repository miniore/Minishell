/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:21:44 by frlorenz          #+#    #+#             */
/*   Updated: 2025/05/20 19:21:06 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fill_env(t_list *backpack, char **envp)
{
    t_env   *env;
    int i;
    char **lst;

    env = NULL;
    lst = var_list(envp);
    i = 0;
    while(lst[i])
    {
        env_add_last(env, new_node(lst[i], getenv(lst[i])));
        i++;
    }
    ft_lstadd_back(backpack, ft_lstnew(env));
}

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
    lst = (char **) calloc(i + 1, sizeof (char **));
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
    name = (char *) calloc(i + 1, sizeof(char *));
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

void free_env(char **lst, t_env **env)
{
    int i;
    t_env *act;
    
    i = 0;
    while(lst[i])
    {
        free(lst[i]);
        i++;
    }
    free(lst);
    act = *env;
     while(act->next != NULL)
     {
         act = act->next;
         free(act);
     }
    free(*env);
}
