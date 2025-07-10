/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:43:39 by miniore           #+#    #+#             */
/*   Updated: 2025/07/10 17:18:16 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char *ft_get_var_value(t_env *env, char *var_name)
{
    t_env   *node;
    char    *value;
    
    node = search_node(&env, var_name);
    if(!node)
        return(NULL);
    value = ft_strdup(node->content);
    return(value);
}

static char *ft_join_tok(t_backpack *backpack, char *res_tok, char *var)
{
    char    *var_value;
    
    var_value = ft_get_var_value(backpack->env, var);
    if(var_value)
        res_tok = ft_strjoin_shell(res_tok, var_value);
    return(res_tok);
}

char    *ft_exp_var(t_backpack *backpack, char *token) //GESTIONAR CUANDO HAY $$. SE DEBE INTERPRETAR??
{
    char    *var;
    char    *res_tok;
    char    *str_2_join;
    int     i;
    size_t  len;

    i = 0;
    len = 1;
    res_tok = NULL;
    printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
    while(token[len])
    {
        printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
        while(token[len - 1] != '$' && token[len - 1])
        {
            printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
            len++;
        }
            //len++;                         //Mirar el caso en que haya u espacio despues de $. echo hola$ USER o  simplemente echo $
        printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
        if(len > 1 && !res_tok)
        {
            printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
            res_tok = ft_substr(token, i, (len - 1) - i);
            printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
        }
        else if(res_tok)
        {
            printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
            str_2_join = ft_substr(token, i, (len - 1) - i);
            printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
            res_tok = ft_strjoin(res_tok, str_2_join);
            printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
            free(str_2_join);
        }
        //printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
        i = (int)len;
        while(token[len] && (ft_isalnum(token[len]) || token[len] == '_'))
            len++;
        //printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
        var = ft_substr(token, i, len - i);
        //printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
        res_tok = ft_join_tok(backpack, res_tok, var);
        //printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
        i = (int)len;
        //printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
        free(var);
        //printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
    }
    printf("||((%s En_Linea %d))||=> %s\n", __FILE__,__LINE__, "ERROR");
    return(res_tok);
}
