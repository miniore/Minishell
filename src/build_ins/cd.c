/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:44 by frlorenz          #+#    #+#             */
/*   Updated: 2025/06/12 12:28:00 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd(t_list *arg, t_env *env)
{
    char *temp;
    t_env *pwd;
    t_env *old_pwd;
    t_env *home;

    pwd = search_node(&env, "PWD");
    old_pwd = search_node(&env, "OLDPWD");
    home = search_node(&env, "HOME");
    if(!arg)
    {
        if (chdir(home->content) == -1)
            perror("cd");
        else
        {
            temp = pwd->content;
            pwd->content = home->content;
            old_pwd->content = temp;
        }
            
    }
    else if(ft_lstsize(arg) == 1)
    {
        if (ft_strcmp((char *)arg->content, "-") == 0)
        {
            if (chdir(old_pwd->content) == -1)
                perror("cd");
            else
            {
                temp = pwd->content;
                pwd->content = getcwd(NULL, 0);
                printf("%s\n", pwd->content);
                old_pwd->content = temp;
            }
        }
        else if (chdir((char *)arg->content) == -1)
           perror("cd"); 
        else
        {
            temp = pwd->content;
            pwd->content = getcwd(NULL, 0);
            old_pwd->content = temp;
        }
    }
    else
        perror("cd: too many arguments");
}
