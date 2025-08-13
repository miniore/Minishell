/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:44 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/13 18:51:47 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_swap_pwd(t_env *pwd, t_env *old_pwd, char *temp)
{
    char *tmp;
    char    *tmp_2_free;
    
    if(!old_pwd)
        free(temp);
    else
    {
        tmp_2_free = old_pwd->content;
        old_pwd->content = temp;
        free(tmp_2_free);
    }
    if (pwd != NULL)
    {
        tmp = pwd->content;
        pwd->content = getcwd(NULL, 0);
        if(!pwd->content)
        {
            free(tmp);
            return(EXIT_FAILURE);
        }
        free(tmp);
    }
    return(EXIT_SUCCESS);
}

static void ft_cd_home(t_backpack *backpack, t_env *pwd, t_env *old_pwd, t_env *home)
{
    char *temp;
    char *tmp_op_free;
    
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
                temp = pwd->content;
                if (old_pwd != NULL)
                {
                    tmp_op_free = old_pwd->content;
                    old_pwd->content = ft_strdup(temp);
                    free(tmp_op_free);
                }
                pwd->content = ft_strdup(home->content);
                free(temp);
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

static int ft_commond_cd(t_backpack *backpack, t_env *pwd, t_env *old_pwd)
{
    char *temp;
    
    temp = getcwd(NULL, 0);
    if (chdir(backpack->commands_lst[backpack->n].arguments->content) == -1)
    {
        free(temp);
        return(EXIT_FAILURE);
    }
    else
    {
        if(ft_swap_pwd(pwd, old_pwd, temp))
            ft_put_syserr(backpack, "Minichelita");
    }
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
            if(ft_commond_cd(backpack, pwd, old_pwd))
                ft_put_pererr(backpack, "Minichelita: cd: No such file or directory\n", 1);
        }
    }
    else
        ft_put_pererr(backpack, "Minichelita: cd: too many arguments\n", 1);
}
