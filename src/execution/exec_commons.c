/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:25:06 by frlorenz          #+#    #+#             */
/*   Updated: 2025/06/10 09:50:08 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_split(char **str)
{
    int i;

    i = 0;
    while (str[i])
        free(str[i++]);
    free(str);
}

char *get_cmd(char *cmd, char **envp)
{
    char    **envp_paths;
    char    *path;
    char    *cmd_path;
    int     i;
    
    i = 0;
    while (!ft_strnstr(envp[i], "PATH=", 5))
        i++;
    envp_paths = ft_split(envp[i] + 5, ':');
    i = -1;
    while (envp_paths[++i])
    {
        path = ft_strjoin(envp_paths[i], "/");
        cmd_path = ft_strjoin(path, cmd);
        free(path);
        if (access (cmd_path, F_OK) == 0)
        {
            free_split(envp_paths);
            return (cmd_path);
        }
        free(cmd_path);
    }
    free_split(envp_paths);
    return (NULL);
}

void run_cmd(char **cmd, char **envp)
{
    //char    **cmd_flags;
    char    *path;

    //cmd_flags = ft_split(cmd, ' ');
    path = get_cmd(cmd_flags[0], envp);
    if (!path)
    {
        free_split(cmd);
        free(path);;
    }
    if (execve(path, cmd, envp) == -1)
    {
        free_split(cmd);
        free (path);
    }
}