/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:35:21 by miniore           #+#    #+#             */
/*   Updated: 2025/08/15 17:02:39 by porellan         ###   ########.fr       */
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
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

extern volatile sig_atomic_t g_exit_status;

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
    t_env   *env;
    tok_lst *commands_lst;
    t_redir *new_redir;
    t_redir *tmp;
    size_t     commands_nb;
    size_t  len;
    int     i;
    int     n;
    int     cmd_flag;
    int     red_flag;
    int     err_flag;
    char    *aux_str;
    char    *token;
    char    *str_2_join;
    int     exit_status;
};

int     ft_get_command(t_backpack *backpack, char *input);
void    ft_extract_tokens(t_backpack *backpack, char *command);
char    *ft_exp_var(t_backpack *backpack, char *token);
char    *ft_var_found(t_backpack *backpack, char *token, char *res_tok, int *i, int *start);
void    ft_redirections(t_backpack *backpack, char *command);
void    ft_save_tok(t_backpack *backpack);
void    ft_save_redir(t_backpack *backpack);

void	ft_extract_content(t_backpack *backpack, char *command);
int		ft_syntax_parse(t_backpack *backpack, char *input);
int     ft_redir_syntax(char *input);
size_t	ft_ignore_qargs(char *command, size_t len);
char    *ft_get_var_value(t_env *env, char *var_name);

int		ft_is_redirct(char c);
int		ft_is_space(char c);
int		ft_is_quotes(char c);
int		ft_is_dquotes(char c);

void	free_array(char **array);
void    free_command_list(tok_lst *commands_lst, size_t size);
char    *ft_strjoin_free(char *s1, char *s2);

void    ft_put_pererr(t_backpack *backpack, char *err, int n);
void    ft_put_syserr(t_backpack *backpack, char *err);
void    ft_put_syserr_exit(t_backpack *backpack, char *err);

void	ft_cmd_free(t_backpack *backpack);
void	ft_exit_free(t_backpack *backpack);
void	ft_final_free(t_backpack *backpack);

//Build_ins
void executor(t_backpack *backpack, char **envp, t_env *path);
void    pwd(t_backpack *backpack);
//void echo(t_list *arg);
void    cd(t_backpack *backpack);
void    ft_echo(t_list *arg);
void    ft_export(t_backpack *backpack);
void	ft_unset(t_backpack *backpack);
void    ft_exit(t_backpack *backpack);

//Stack envp
void	env_add_last(t_env **lst, t_env *new);
t_env *new_node(char *var, char *content);
char **var_list(char **envp);
char *name_var(char *var);
void ft_free_env(t_env *env);
int fill_env(t_env **env, char **envp);
t_env *search_node(t_env **env, char *name);
void erase_node(t_env **env, t_env *node);
void modify_node(t_env *node, char *var, char *content); // esta funcion requiere que los nuevos valores esten en memoria
int ft_env(t_backpack *backpack, int option);

//EXEC COMMONS
//void run_cmd(char **cmd, t_env *env, char **envp);
int exec_loop(t_backpack *backpack, char **envp);
void    process_tok(t_backpack *backpack, t_env *env, char **envp);
int    ft_exec_redir(t_backpack *backpack, t_redir *redirection);
void	exit_error(void);

void ft_cmond_singel(t_backpack *backpack, char **envp, t_env *path);
void ft_bin_singel(t_backpack *backpack, char **envp, t_env *path);
//void ft_pipe_redir(t_backpack *backpack, int prev_fd, int *pipe_fd);
void ft_pipe_son(t_backpack *backpack, int prev_fd, int *pipe_fd, char **envp, t_env *path);
int ft_pipe_father(t_backpack *backpack, char **envp, t_env *path, int prev_fd);

//SIGNALS
void handle_ctrl_c(int sig);
void hdoc_ctrl_c(int sig);

//redirtools
int ft_n_hdocs(t_redir *redirection);
int ft_n_redout(t_redir *redirection);
int fr_input_handler(t_redir *redirection, int pipe_fd);
int ft_lst_rdo(t_redir *redirection);

#endif