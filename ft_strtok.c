/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:12:52 by miniore           #+#    #+#             */
/*   Updated: 2025/02/20 16:16:06 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_valid_com(char *command)
{
    if(!strcmp(command, "echo"))
        printf("%s\n", command);
    // {
    //     if(echo_parse(command))
    //         return(EXIT_FAILURE);
    // }
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
        return(EXIT_FAILURE);
    return(EXIT_SUCCESS);
}

// int ft_strtok(char *str)
// {
//     int     i;
//     int     j;
//     //char    *command;

//     i = 0;
//     if(!str)
//         return(EXIT_FAILURE);
//     printf("Oy");
//     //command = (char *)malloc(strlen(str) + 2);
//     while(str[i] == 9 || str[i] == 32)
//         i++;
//     while(str[i] != 9 || str[i] != 32)
//     {
//         command[j] = str[i];
//         i++;
//         j++;
//     }
//     command[j] = '\0';
//     printf("Uy");
//     if(ft_valid_com(command))
//         return(EXIT_FAILURE);
//     return(EXIT_SUCCESS);
// }
