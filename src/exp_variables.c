/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:43:39 by miniore           #+#    #+#             */
/*   Updated: 2025/05/27 12:06:55 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_save_exp_arg(t_backpack *backpack, char *res_tok)
{
    t_list  *temp;

    if(!backpack->flag)
    {
        backpack->commands_lst[backpack->n].command = res_tok;
        return ;
    }
    temp = ft_lstnew(res_tok);
    ft_lstadd_back(&backpack->commands_lst[backpack->n].arguments, temp); 
}

static char	*ft_strjoin_shell(char const *s1, char *s2)
{
	char	*new_str;
	size_t	new_str_len;
	int		i;
	int		j;

	if (!s1)
		return (s2);
	new_str_len = ft_strlen(s1) + ft_strlen(s2);
	new_str = ft_calloc(new_str_len + 1, 1);
	if (new_str == NULL)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	return (new_str);
}

// Hacer funcion de buscar el contenido de variable de entorno en la lista para sustituir getenv

static char *ft_join_tok(char *res_tok, char *var) //Añadir backpack!!!!!1
{
    char    *var_value;
    
    var_value = getenv(var);
    if(var_value)
        res_tok = ft_strjoin_shell(res_tok, var_value);
    return(res_tok);
}

void    ft_exp_var(t_backpack *backpack, char *token) //GESTIONAR CUANDO HAY $$. SE DEBE INTERPRETAR??
{
    char    *var;
    char    *res_tok;
    int     flag;
    int     i;
    size_t  len;

    flag = 1;
    i = 0;
    len = 1;
    res_tok = NULL;
    while(token[len] != '\0')
    {
        while(token[len - 1] != '$')
            len++;                          //Mirar el caso en que haya u espacio despues de $. echo hola$ USER o  simplemente echo $
        if(len > 1 && flag == 1)
            res_tok = ft_substr(token, i, (len - 1) - i);
        i = (int)len;
        while(token[len] != '\0' && token[len] != '$')
            len++;
        var = ft_substr(token, i, len - i);
        res_tok = ft_join_tok(res_tok, var);
        flag = 0;
        free(var);
    }
    ft_save_exp_arg(backpack, res_tok);
}
