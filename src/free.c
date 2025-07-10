/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:12:31 by miniore           #+#    #+#             */
/*   Updated: 2025/07/09 14:39:04 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// void free_list(t_list *commands_lst)
// {
//     t_list *temp;
//     tok_lst *cmd;

//     while (commands_lst)
//     {
//         temp = commands_lst;
//         cmd = (tok_lst *)commands_lst->content;
//         free(cmd->command);
// 		if(cmd->arguments)
// 			ft_lstclear(&cmd->arguments, free);
// 		if(cmd->redirection)
// 			ft_lstclear(&cmd->redirection, free);
//         free(cmd->option);
//         free(cmd);
//         commands_lst = commands_lst->next;
//         free(temp);
//     }
// }

void free_redirections(t_redir *redir)
{
    t_redir *tmp;

    while (redir)
    {
        tmp = redir->next;
        free(redir->op);
        free(redir->del);
        free(redir);
        redir = tmp;
    }
}

void free_arguments(t_list *args)
{
    t_list *tmp;

    while (args)
    {
        tmp = args->next;
        free(args->content); // cada argumento es un string duplicado
        free(args);
        args = tmp;
    }
}

void free_command_list(tok_lst *commands_lst, size_t size)
{
    size_t i = 0;

    while (i < size)
    {
        free_command(&commands_lst[i]);
        i++;
    }
    free(commands_lst);
}

void free_env(t_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env->next;
        free(env->var);
        free(env->content);
        free(env);
        env = tmp;
    }
}

void free_backpack(t_backpack *bp)
{
    if (!bp)
        return;
    free_env(bp->env);
    free_command_list(bp->commands_lst, bp->commands_nb);
    free(bp->token);
    // free(bp->aux_str);
    // free(bp->str_2_join);
    // No hace falta liberar bp->new_redir ni bp->tmp si ya están dentro de commands
}

void	ft_free()
{
	
}