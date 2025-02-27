/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:12:52 by miniore           #+#    #+#             */
/*   Updated: 2025/02/27 13:32:02 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int save_token()
{
    // mirar si es opcion de comando, argumento, variable de entorno o redireccion
}

int ft_tokenize(char *input)       //Darle una vuelta y MIRAR ESTRUCTURAS CON FRAN!!!!!
{
    static int i;
    size_t  len;
    char    *token;

    i = 0;
    while(!is_space(input[i]))
        i++;
    if(is_quotes(input[i]))
        //len = funcion para comillas simples
    else if(is_dquotes(input[i]))
        //len = funcion para comillas dobles
    else
        //len = funcion para otros
    //len = i;
    // while(input[len] != 32 && input[len] != 34 && input[len] != 39 &&
    //         input[len] != 124 && input[len] != 60 && input[len] != 62) //meter en la funcion para otros
    //     len++;
    token = ft_substr(input, i, len);
    if(!save_token(token))
        free(token);
    else
        return(EXIT_FAILURE);
    if(input[len] != '\0')
        ft_tokenize(input);
    return(EXIT_SUCCESS)
}





 int ft_valid_com(char *command)
 {
     if(!strcmp(command, "echo"))
         printf("%s\n", command);
     /* {
          if(echo_parse(command))
              return(EXIT_FAILURE);
      }
     else if(!strcmp(command, "cd"))
         printf("%s\n", command);
     else if(!strcmp(command, "pwd"))
         printf("%s\n", command);
     else if(!strcmp(command, "export"))
         printf("%s\n", command);
     else if(!strcmp(command, "unset"))
         printf("%s\n", command);
     else if(!strcmp(command, "env"))
         printf("%s\n", command);
     else
         return(EXIT_FAILURE);*/
     return(EXIT_SUCCESS);
 }


// int	save_tokens(char *input)
// {
// 	t_list	*tokens;
// 	int	i;

// 	i = 0;
// 	while(input[i])
// 	{
// 		while(input)
// 			i++;
// 		if(input[i] == 34 || input[i] == 39)
// 		{
			
// 		}
		
// 		else
// 			i++;
// 	}
// 	return(EXIT_SUCCESS);
// }

// int ft_strtok(char *str, const char *del)
// {
// 	int	i;
// 	int	j;

// 	while()
// }

    // int     i;
    // int     j;
    // //char    *command;

    // i = 0;
    // if(!str)
    //     return(EXIT_FAILURE);
    // printf("Oy");
    // //command = (char *)malloc(strlen(str) + 2);
    // while(str[i] == 9 || str[i] == 32)
    //     i++;
    // while(str[i] != 9 || str[i] != 32)
    // {
    //     command[j] = str[i];
    //     i++;
    //     j++;
    // }
    // command[j] = '\0';
    // printf("Uy");
    // if(ft_valid_com(command))
    //     return(EXIT_FAILURE);
    // return(EXIT_SUCCESS);