#include "minishell.h"

void echo(t_list *arg)
{
    t_list *temp;
    int i;
    bool opt;

    temp = arg;
    opt = false;
    i = 0;
    while(temp->next != NULL)
    {
        if(ft_strncmp(temp->content, "-n", 3)  == 0 && i == 0)
            opt = true;
        else
            printf("%s ", (char*)temp->content);
        temp = temp->next;
        i++;
    }
    printf("%s", (char*)temp->content);
    if (opt == false)
        printf("\n");
}

