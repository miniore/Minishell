/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:35:21 by miniore           #+#    #+#             */
/*   Updated: 2025/02/20 18:55:26 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "Libft/libft.h"
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
}	tok_lst;


// int ft_strtok(char *str);
int ft_valid_com(char *command);

#endif