/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:01:59 by frlorenz          #+#    #+#             */
/*   Updated: 2025/07/29 18:51:17 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int fill_env(t_env **env, char **envp)
{
    int i;
    char **lst;
    char *value;

    lst = var_list(envp);
    if (!lst[0])
        env_add_last(env, new_node("PWD", getcwd(NULL, 0)));
    else
    {
        i = 0;
        while(lst[i])
        {
            value = getenv(lst[i]);
            if (value)
                value = ft_strdup(value);
            env_add_last(env, new_node(lst[i], value));
            i++;
        }
        free_array(lst);
    }
    return(1);
}

t_env *search_node(t_env **env, char *name)
{
    t_env   *node;
    int i;
    
    node = *env;
    i = ft_strlen(name);
    while(node)
    {
        if (ft_strncmp(node->var, name, i + 1) == 0)
            return (node);
        node = node->next;
    }
    return(NULL);
}

void modify_node(t_env *node, char *var, char *content)
{
    char *temp;
    char *temp_content;

    if (var != NULL)
    {
        temp = node->var;
        node->var = var;
        free(temp);
    }
    temp_content = node->content;
    node->content = content;
    free(temp_content);
}

void erase_node(t_env **env, t_env *node)
{
    t_env *prev;
    t_env *next;

    prev = node->prev;
    next = node->next;
    if(!next)
        prev->next = NULL;
    else
    {
        if(!prev)
            *env = next;
        else
        {
            prev->next = next;
            next->prev = prev;
        }
    }
    free(node->var);
    free(node->content);
    free(node);
}

void    ft_free_env(t_env *env)
{
    t_env   *tmp;
    
    while(env)
    {
        tmp = env->next;
        free(env->var);
        free(env->content);
        free(env);
        env = tmp;
    }
}
