/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniore <miniore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:17:56 by frlorenz          #+#    #+#             */
/*   Updated: 2025/08/06 20:58:58 by miniore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pwd(t_backpack *backpack)
{
    char *path;  
    
    path = getcwd(NULL, 0); // getcwd asigna memoria automáticamente????????
    if (path == NULL)
    {
        ft_put_syserr(backpack, "getcwd"); //Mirar como sale el error!!!!!!
        return ;
    }
    printf("%s\n", path);
    free(path); // No olvidar liberar!!!!!!!!
}
