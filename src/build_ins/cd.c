/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:44 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/12 14:14:04 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_swap_pwd(t_env *pwd, t_env *old_pwd, char *temp)
{
    char *tmp;
    
    if(!old_pwd)
        free(temp);
    else
        old_pwd->content = temp;
    if (pwd != NULL)
    {
        tmp = pwd->content;
        pwd->content = getcwd(NULL, 0);
        if(!pwd->content)
            
        free(tmp);
    }
}

static void ft_cd_home(t_backpack *backpack, t_env *pwd, t_env *old_pwd, t_env *home)
{
    char *temp;
    
    if (!home)
        ft_put_pererr(backpack, "cd: not set HOME\n", 1);
    else
    {
        if (chdir(home->content) == -1)
            ft_put_pererr(backpack, "Minichelita: cd: No such file or directory\n", 1);    
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

static void ft_oldpwd(t_backpack *backpack, t_env *pwd, t_env *old_pwd)
{
    char *temp;
    char    *tmp_2_free;

    if (!old_pwd)
        ft_put_pererr(backpack, "cd: not set OLDPWD\n", 1);
    else
    {
        if (chdir(old_pwd->content) == -1)
            ft_put_pererr(backpack, "Minichelita: cd: No such file or directory\n", 1);
        else
        {
            if (pwd != NULL)
            {
                temp = pwd->content;
                pwd->content = getcwd(NULL, 0);
                printf("%s\n", pwd->content);
                if (old_pwd != NULL)
                {
                    tmp_2_free = old_pwd->content;
                    old_pwd->content = temp;
                    free(tmp_2_free);
                }
            }
        }
    }
        
}

static int ft_commond_cd(char *path, t_env *pwd, t_env *old_pwd)
{
    char *temp;
    
    temp = getcwd(NULL, 0);
    if (chdir(path) == -1)
        return(EXIT_FAILURE);
    else
        ft_swap_pwd(pwd, old_pwd, temp);
    return(EXIT_SUCCESS);
}

void cd(t_backpack *backpack)
{
    t_env *pwd;
    t_env *old_pwd;
    t_env *home;

    pwd = search_node(&backpack->env, "PWD");
    old_pwd = search_node(&backpack->env, "OLDPWD");
    home = search_node(&backpack->env, "HOME");
    if(!backpack->commands_lst[backpack->n].arguments)
        ft_cd_home(backpack, pwd, old_pwd, home);           
    else if(ft_lstsize(backpack->commands_lst[backpack->n].arguments) == 1)
    {
        if (ft_strcmp(backpack->commands_lst[backpack->n].arguments->content, "-") == 0)
            ft_oldpwd(backpack, pwd, old_pwd); 
        else
        {
            if(ft_commond_cd(backpack->commands_lst[backpack->n].arguments->content, pwd, old_pwd))
                ft_put_pererr(backpack, "Minichelita: cd: No such file or directory\n", 1);
        }
    }
    else
        ft_putstr_fd("Minichelita: cd: too many arguments\n", 2);
}
