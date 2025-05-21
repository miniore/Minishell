/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:17:56 by frlorenz          #+#    #+#             */
/*   Updated: 2025/05/06 12:29:34 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pwd(void)
{
    char *path;  
    
    path = getcwd(NULL, 0); // getcwd asigna memoria automáticamente????????
    if (path != NULL) {
        printf("%s\n", path);
        free(path);  // No olvidar liberar!!!!!!!!
    } else {
        perror("getcwd() error"); //Mirar como sale el error!!!!!!
    }
}