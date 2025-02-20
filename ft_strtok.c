/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:12:52 by miniore           #+#    #+#             */
/*   Updated: 2025/02/20 19:37:47 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int ft_valid_com(char *command)
// {
//     if(!strcmp(command, "echo"))
//         printf("%s\n", command);
//     // {
//     //     if(echo_parse(command))
//     //         return(EXIT_FAILURE);
//     // }
//     else if(!strcmp(command, "cd"))
//         printf("%s\n", command);
//     else if(!strcmp(command, "pwd"))
//         printf("%s\n", command);
//     else if(!strcmp(command, "export"))
//         printf("%s\n", command);
//     else if(!strcmp(command, "unset"))
//         printf("%s\n", command);
//     else if(!strcmp(command, "env"))
//         printf("%s\n", command);
//     else
//         return(EXIT_FAILURE);
//     return(EXIT_SUCCESS);
// }

int	ft_isdel(char c)
{
	if(c == 34 || c == 39)                     //Commillas simples o comillas dobles
		return(EXIT_FAILURE);
	return(EXIT_SUCCESS);
}

int	save_tokens(char *input)
{
	t_list	*tokens;
	int	i;

	i = 0;
	while(input[i])
	{
		while(input)
			i++;
		if(input[i] == 34 || input[i] == 39)
		{
			
		}
		
		else
			i++;
	}
	return(EXIT_SUCCESS);
}

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