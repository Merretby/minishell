/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:38:57 by monachit          #+#    #+#             */
/*   Updated: 2024/05/18 12:39:08 by monachit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_arg(char **str)
{
    int i;
    int j;
    
    while (str[i])
    {
        j = 0;
        if (str[i][j] == '-')
        {
            j++;
            while (str[i][j] && str[i][j] == 'n')
                j++;
            if (!str[i][j])
                return (j);
        }
        i++;
    }
    return (0);
}

void    ft_print(char **s, int i)
{
    int k;

    k = 0;
    while (s[i])
    {
        k = 0;
        while(s[i][k])
        {
            write(1, &s[i][k], 1);
            k++;
        }
        if (s[i + 1])
            write(1, " ", 1);
        i++;
    }
}
void      ft_print(char **str)
{
    int i;
    int j;

    i = 1;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            write(1, &str[i][j], 1);
            j++;
        }
        if (str[i + 1])
            write(1, " ", 1);
        i++;
    }
    write(1, "\n", 1);
}
int     ft_echo(t_node *node)
{
    int i;
    
    i = check_arg(node->data->cmd->args);
    if (i > 0)
        ft_print(node->data->cmd->args, i);
    else
        ft_print2(node->data->cmd->args);
    return (0);
}