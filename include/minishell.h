/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:35:21 by miniore           #+#    #+#             */
/*   Updated: 2025/06/26 16:02:13 by frlorenz         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>

typedef struct  s_redir t_redir;
typedef struct  s_tok tok_lst;
typedef struct  s_env t_env;
typedef struct  s_backpack t_backpack;

struct s_redir
{
    char    *op;
    char    *del;
    struct s_redir  *next;
};

struct s_tok
{
	char	*command;
	t_list	*arguments;
	t_redir	*redirection;
};

//Estructura para listar el enviroment
struct s_env
{
    char *var;
    char *content;
    struct s_env *prev;
    struct s_env *next;
};

struct s_backpack
{
    t_env *env;
    tok_lst *commands_lst;
    t_redir *new_redir;
    t_redir *tmp;
    size_t     commands_nb;
    size_t  len;
    int     i;
    int     n;
    int     cmd_flag;
    int     red_flag;
    char    *aux_str;
    char    *token;
    char    *str_2_join;
};

int ft_get_command(t_backpack *backpack, char *input);
void    ft_extract_tokens(t_backpack *backpack, char *command);
void    ft_redirections(t_backpack *backpack, char *command);
void    ft_save_redir(t_backpack *backpack);

void	ft_extract_content(t_backpack *backpack, char *command);
int		ft_syntax_parse(char *input);
size_t	ft_ignore_qargs(char *command, size_t len);

int		ft_is_redirct(char c);
int		ft_is_space(char c);
int		ft_is_quotes(char c);
int		ft_is_dquotes(char c);

void	free_array(char **array);
//void	free_list(t_list *commands_list);

// void    ft_save_command(t_backpack *backpack, char *command, int i);
// void    ft_save_qarg(t_backpack *backpack, char *command, int i);
// void    ft_save_arg(t_backpack *backpack, char *command, int i);
char    *ft_exp_var(t_backpack *backpack, char *token);

//Build_ins
void executor(t_backpack *backpack, char **envp);
int pwd(t_env **env);
//void echo(t_list *arg);
void cd(t_list *arg, t_env *env);
void    ft_echo(t_list *arg);
void    ft_export(t_backpack *backpack);
void	ft_unset(t_backpack *backpack);

//Stack envp
void	env_add_last(t_env **lst, t_env *new);
t_env *new_node(char *var, char *content);
char **var_list(char **envp);
char *name_var(char *var);
void free_env(t_env **env);
int fill_env(t_env **env, char **envp);
t_env *search_node(t_env **env, char *name);
void erase_node(t_env **env, t_env *node);
void modify_node(t_env *node, char *var, char *content); // esta funcion requiere que los nuevos valores esten en memoria
int ft_env(t_env **env);

//EXEC COMMONS
void run_cmd(char **cmd, char **envp);
int exec_loop(t_backpack *backpack, char **envp);
char **process_tok(tok_lst *token);
void	exit_error(void);

#endif