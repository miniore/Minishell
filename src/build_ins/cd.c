/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:44 by frlorenz          #+#    #+#             */
/*   Updated: 2025/07/24 11:59:59 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_swap_pwd(t_env *pwd, t_env *old_pwd, char *temp)
{
    if(!old_pwd)
        free(temp);
    else
        old_pwd->content = temp;
    if (pwd != NULL)
        pwd->content = getcwd(NULL, 0);
}

static void ft_cd_home(t_env *pwd, t_env *old_pwd, t_env *home)
{
    char *temp;
    
    if (!home)
        ft_putstr_fd("cd: not set HOME\n", 2);    
    else
    {
        if (chdir(home->content) == -1)
        {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(home->content, 2);
            ft_putstr_fd(": No such file or directory\n", 2);
        }       
        else
        {
            if (pwd != NULL)
            {
                if (old_pwd != NULL)
                {
                    temp = pwd->content;
                    old_pwd->content = temp;
                }
                pwd->content = home->content;
            }  
        }
    }    
}

static void ft_oldpwd(t_env *pwd, t_env *old_pwd)
{
    char *temp;

    if (!old_pwd)
        ft_putstr_fd("cd: not set OLDPWD\n", 2);
    else
    {
        if (chdir(old_pwd->content) == -1)
        {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(old_pwd->content, 2);
            ft_putstr_fd(": No such file or directory\n", 2);
        }
        else
        {
            if (pwd != NULL)
            {
                temp = pwd->content;
                pwd->content = getcwd(NULL, 0);
                printf("%s\n", pwd->content);
                if (old_pwd != NULL)
                    old_pwd->content = temp;
            }
        }
    }
        
}

static void ft_commond_cd(char *path, t_env *pwd, t_env *old_pwd)
{
    char *temp;
    
    temp = getcwd(NULL, 0);
    if (chdir(path) == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(" No such file or directory\n", 2);
    }
    else
        ft_swap_pwd(pwd, old_pwd, temp);
}

void cd(t_list *arg, t_env *env)
{
    t_env *pwd;
    t_env *old_pwd;
    t_env *home;

    pwd = search_node(&env, "PWD");
    old_pwd = search_node(&env, "OLDPWD");
    home = search_node(&env, "HOME");
    if(!arg)
        ft_cd_home(pwd, old_pwd, home);           
    else if(ft_lstsize(arg) == 1)
    {
        if (ft_strcmp((char *)arg->content, "-") == 0)
            ft_oldpwd(pwd, old_pwd); 
        else
            ft_commond_cd((char *)arg->content, pwd, old_pwd);
    }
    else
        ft_putstr_fd("cd: too many arguments\n", 2);
}
