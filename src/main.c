/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:40:48 by miniore           #+#    #+#             */
/*   Updated: 2025/08/15 19:39:05 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

static int	ft_void_input(char *input)
{
	int	i;

	if (*input == '\0')
		return (EXIT_FAILURE);
	i = 0;
	while (input[i] == 32)
		i++;
	if (input[i] == '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_bp	*ft_bp_creator(t_bp *bp)
{
	bp = (t_bp *)ft_calloc(1, sizeof(t_bp));
	if (!bp)
		ft_put_pererr(bp, "Minichelita: malloc error.\n", 1);
	return (bp);
}

static int	ft_input_loop(t_bp *bp, char *input)
{
	if (g_exit_status == 130)
		bp->exit_status = g_exit_status;
	if (!input)
	{
		g_exit_status = 131;
		bp->commands_nb = 0;
		printf("Nos vamos. Saliendo.\n");
		ft_final_free(bp);
		exit(g_exit_status);
	}
	g_exit_status = 0;
	if (ft_void_input(input))
	{
		free(input);
		return (EXIT_FAILURE);
	}
	add_history(input);
	if (ft_get_command(bp, input))
	{
		if (bp->exit_status != 258)
			ft_cmd_free(bp);
		free(input);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_bp	*bp;
	char	*input;

	(void)argv;
	bp = NULL;
	if (argc != 1)
		return (EXIT_FAILURE);
	bp = ft_bp_creator(bp);
	if (!bp)
		return (EXIT_FAILURE);
	fill_env(&bp->env, envp);
	while (1)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, handle_ctrl_c);
		input = readline("Minichelita> ");
		if (ft_input_loop(bp, input))
			continue ;
		exec_loop(bp, envp);
		ft_cmd_free(bp);
		free(input);
	}
	rl_clear_history();
	ft_final_free(bp);
	return (EXIT_SUCCESS);
}
