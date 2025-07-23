/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:44 by frlorenz          #+#    #+#             */
/*   Updated: 2025/07/23 12:57:09 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_fillpwd(t_env **pwd, t_env **old_pwd, t_env **home, t_env **env)
{
    int i;

    i = 0;
    *pwd = search_node(env, "PWD");
    if (!*pwd)
        i = 1;
    *old_pwd = search_node(env, "OLDPWD");
    if (!*old_pwd)
        i = 2;
    *home = search_node(env, "HOME");
    if (!*home)
        i = 3;
    return(i);
}

static void ft_cd_home(t_env *pwd, t_env *old_pwd, t_env *home, int check)
{
    char *temp;
    
    if (check == 3)
    {
        if (chdir(home->content) == -1)
        {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(home->content, 2);
            ft_putstr_fd(": No such file or directory\n", 2);
        }       
        else
        {
            temp = pwd->content;
            pwd->content = home->content;
            old_pwd->content = temp;
        }
    }
    else
        ft_putstr_fd("cd: not set HOME\n", 2);
}

static void ft_oldpwd(t_env *pwd, t_env *old_pwd, int check)
{
    char *temp;

    if (check == 2)
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
    else
        ft_putstr_fd("cd: not set OLDPWD\n", 2);
}

static void ft_commond_cd(char *path, t_env *pwd, t_env *old_pwd, int check, t_env **env)
{
    char *temp;
    
    if (chdir(path) == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(" No such file or directory\n", 2);
    }
    if (check == 0)
    {
        temp = pwd->content;
        pwd->content = getcwd(NULL, 0);
        old_pwd->content = temp;
    }
    else if (check == 1)
    {
        env_add_last(env, new_node("OLDPWD", pwd->content));
        pwd->content = getcwd(NULL, 0);
    }
}

void cd(t_list *arg, t_env *env)
{
    int check;
    t_env *pwd;
    t_env *old_pwd;
    t_env *home;

    check = ft_fillpwd(&pwd, &old_pwd, &home, &env);
    if(!arg)
        ft_cd_home(pwd, old_pwd, home, check);           
    else if(ft_lstsize(arg) == 1)
    {
        if (ft_strcmp((char *)arg->content, "-") == 0)
            ft_oldpwd(pwd, old_pwd, check); 
        else
            ft_commond_cd((char *)arg->content, pwd, old_pwd, check, &env);
    }
    else
        ft_putstr_fd("cd: too many arguments\n", 2);
}
