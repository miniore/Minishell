/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:25:06 by frlorenz          #+#    #+#             */
/*   Updated: 2025/06/11 18:01:43 by frlorenz         ###   ########.fr       */
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
    char    *path;

    path = get_cmd(cmd[0], envp);
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

//Funcion que genera un array 2D con el comando y sus flags a partir de un tok_lst
//para poder pasarlo al execv mas adelante
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