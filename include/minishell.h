/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:35:21 by miniore           #+#    #+#             */
/*   Updated: 2025/05/20 19:35:00 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdbool.h>

typedef struct  s_tok tok_lst;
typedef struct  s_env t_env;
typedef struct  s_backpack t_backpack;


struct s_tok
{
	char	*command;
	t_list	*arguments;
	t_list	*redirection;
};

//Estructura para listar el enviroment
typedef struct s_env
{
    char *var;
    char *content;
    struct s_env *prev;
    struct s_env *next;
};

typedef struct backpack
{
    t_env *env;
    tok_lst *commands_lst;
    size_t     commands_nb;
    size_t  len;
    int     n;
    int     flag;
};

int ft_get_command(t_list **backpack, char *input);
int ft_tokenize(t_list **backpack, char *command);

size_t	ft_extract_content(char *command, size_t len);
int		ft_syntax_parse(char *input);
size_t	ft_ignore_qargs(char *command, size_t len);

int		ft_is_redirct(char c);
int		ft_is_space(char c);
int		ft_is_quotes(char c);
int		ft_is_dquotes(char c);

void	free_array(char **array);
void	free_list(t_list *commands_list);

void    ft_save_command(t_list *backpack, char *command, int i, size_t len);
size_t  ft_save_qarg(t_list *backpack, char *command, int i, size_t len);
void    ft_save_arg(t_list * backpack, char *command, int i, size_t len);
void    ft_exp_var(t_list *backpack, char *token);

//Build_ins
void executor(tok_lst *com_tokens, t_env **env);
void pwd(void);
//void echo(t_list *arg);
void cd(t_list *arg);
void    ft_echo(t_list *arg);

//Stack envp
void fill_env(t_list *backpack, char **envp);
void	env_add_last(t_env **lst, t_env *new);
t_env *new_node(char *var, char *content);
char **var_list(char **envp);
char *name_var(char *var);
void free_env(char **lst, t_env **env);


#endif