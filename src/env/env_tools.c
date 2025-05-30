/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:01:59 by frlorenz          #+#    #+#             */
/*   Updated: 2025/05/30 20:04:52 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int fill_env(t_env **env, char **envp)
{
    int i;
    int len;
    char **lst;
    char *value;
    
    lst = var_list(envp);
    i = 0;
    while(lst[i])
    {
        len = strlen(getenv(lst[i]));
        value = (char *) calloc(len + 1, sizeof (char *));
        if (!value)
            return(0);
        value = getenv(lst[i]);
        env_add_last(env, new_node(lst[i], value));
        i++;
    }
    free(lst);
    return(1);
}

t_env *search_node(t_env **env, char *name)
{
    t_env   *node;
    int i;
     
    node = *env;
    i = strlen(name);
    while(node->next != NULL)
    {
        if (strncmp(node->var, name, i) == 0)
            return (node);
        node = node->next;
    }
    return(NULL);
}

void modify_node(t_env *node, char *var, char *content)
{
    char *temp;

    temp = node->var;
    node->var = var;
    free(temp);
    temp = node->content;
    node->content = content;
}

void erase_node(t_env *node)
{
    t_env *temp;
    t_env *prev;
    t_env *next;

    temp = node;
    prev = node->prev;
    next = node->next;
    prev->next = next;
    next->prev = prev;
    //free(node->var);
    //free(node->content);
    free(node);
}

void free_env(t_env **env)
{
    t_env *act;
    t_env *temp;
    
    act = *env;
     while(act->next != NULL)
     {
        temp = act;
        free(act->var);
        //free(act->content);
        act = act->next;
        free(temp);
     }
}