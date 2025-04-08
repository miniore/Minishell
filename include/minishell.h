/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:35:21 by miniore           #+#    #+#             */
/*   Updated: 2025/04/02 18:47:28 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../Libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>


typedef struct tokens
{
	char	*command;
	char	*option;
	t_list	*arguments;
	t_list	*redirection;
}	tok_lst;



int 	ft_get_command(char *input);
int 	ft_tokenize(t_list **commands_lst, char *command);

size_t	ft_extract_content(char *command, size_t len);
int		ft_syntax_parse(char *input);
size_t	ft_ignore_qargs(char *command, size_t len);


int		ft_is_redirct(char c);
int		ft_is_space(char c);
int		ft_is_quotes(char c);
int		ft_is_dquotes(char c);

void	free_array(char **array);
void	free_list(t_list *commands_list);

void    ft_save_command(tok_lst *com_tokens, char *command, int i, size_t len);
size_t  ft_save_qarg(tok_lst *com_tokens, char *command, int i, size_t len);
void    ft_save_arg(tok_lst *com_tokens, char *command, int i, size_t len);
void    ft_exp_var(tok_lst *com_tokens,char *token);


#endif