/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:17:56 by frlorenz          #+#    #+#             */
/*   Updated: 2025/04/30 12:22:08 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pwd(void)
{
    char *path = getcwd(NULL, 0);  // getcwd asigna memoria automáticamente????????

    if (path != NULL) {
        printf("Directorio actual: %s\n", path);
        free(path);  // No olvidar liberar!!!!!!!!
    } else {
        perror("getcwd() error"); //Mirar como sale el error!!!!!!
    }
}