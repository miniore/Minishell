/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:25:06 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/15 20:04:51 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

char	*get_cmd(char *cmd, t_env *env)
{
	char	**envp_paths;
	char	*path;
	char	*cmd_path;
	int		i;

	if (!env)
		return (NULL);
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

static void	ft_no_path(t_bp *bp, char *path, char **cmd, t_env *env)
{
	if (!path)
	{
		free_split(cmd);
		free(path);
		ft_free_env(env);
		ft_put_syserr_exit(bp, "Minichelita");
	}
}

static void	run_cmd(t_bp *bp, char **cmd, t_env *env, char **envp)
{
	char	*path;

	if (access(cmd[0], F_OK) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
		{
			free_split(cmd);
			ft_put_syserr_exit(bp, "Minichelita");
		}
	}
	path = get_cmd(cmd[0], env);
	ft_no_path(bp, path, cmd, env);
	if (execve(path, cmd, envp) == -1)
	{
		free_split(cmd);
		free (path);
		ft_free_env(env);
		ft_put_syserr_exit(bp, "Minichelita");
	}
	free(path);
}

void	process_tok(t_bp *bp, t_env *env, char **envp)
{
	int		i;
	char	**cmd;
	t_list	*act;

	i = ft_lstsize(bp->commands_lst[bp->n].arguments);
	cmd = (char **) ft_calloc(i + 2, sizeof (char **));
	if (!cmd)
		return (ft_put_pererr(bp, "Minichelita: malloc error", 1));
	cmd[0] = bp->commands_lst[bp->n].command;
	act = bp->commands_lst[bp->n].arguments;
	i = 1;
	while (act)
	{
		cmd[i] = (char *) act->content;
		i++;
		act = act->next;
	}
	run_cmd(bp, cmd, env, envp);
}
