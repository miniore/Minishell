/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:17:56 by frlorenz          #+#    #+#             */
/*   Updated: 2025/06/19 12:13:00 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd(t_env **env)
{
    (void)env; 
     //t_env *node;

     //node = search_node(env, "PWD");
    // if (node != NULL)
    // {
    //     printf("%s\n", node->content);
    //     return (1);
    // }
    // return (0);
    
    char *path;  
    
    path = getcwd(NULL, 0); // getcwd asigna memoria automáticamente????????
    if (path != NULL) {
        printf("%s\n", path);
        free(path); // No olvidar liberar!!!!!!!!
        return (1);
    } else {
        perror("getcwd() error"); //Mirar como sale el error!!!!!!
    }
    return (0);
}