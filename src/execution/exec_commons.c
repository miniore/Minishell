/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:25:06 by frlorenz          #+#    #+#             */
/*   Updated: 2025/07/30 16:35:22 by frlorenz         ###   ########.fr       */
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

char *get_cmd(char *cmd, t_env *env)
{
    char    **envp_paths;
    char    *path;
    char    *cmd_path;
    int     i;
    
    if (!env)
        return(NULL);
    envp_paths = ft_split(env->content, ':');
    i = 0;
    while (envp_paths[i])
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
        i++;
    }
    free_split(envp_paths);
    return (NULL);
}

void run_cmd(char **cmd, t_env *env, char **envp)
{
    char    *path;
    
    if (access (cmd[0], F_OK) == 0)
    {
        if (execve(cmd[0], cmd, envp) == -1)
        {
            free_split(cmd);
            exit_error();
        }
    }
    path = get_cmd(cmd[0], env);
    if (!path)
    {
        ft_putstr_fd("Command '", 2);
        ft_putstr_fd(cmd[0], 2);
        ft_putstr_fd("' not found.\n", 2);
        free_split(cmd);
        free(path);
        exit(127);
    }
    if (execve(path, cmd, envp) == -1)
    {
        free_split(cmd);
        free (path);
        ft_free_env(env);
        exit_error();
    }
}

char **process_tok(tok_lst *token)
{
    int i;
    char **cmd;
    t_list *act;

    i = ft_lstsize(token->arguments);
    cmd = (char **) ft_calloc(i + 2, sizeof (char **));
    if (!cmd)
        return(NULL);
    //printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
    cmd[0] = token->command;
    act = token->arguments;
    i = 1;
    while(act)
    {
        cmd[i] = (char *) act->content;
        i++;
        act = act->next;
    }
    return(cmd);
}
