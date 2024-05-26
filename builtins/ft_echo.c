/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:38:57 by monachit          #+#    #+#             */
/*   Updated: 2024/05/25 18:26:43 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     check_arg(char *str)
{
    if (str[0] != '-')
        return (0);
    int i;

    i = 1;
    while(str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void    ft_print(char **s)
{
    int i;
    int j;
    
    i = 1;
    while (s[i])
    {
        if (!check_arg(s[i]))
            break;
        i++;
    }
    while(s[i])
    {
        j = 0;
        while (s[i][j])
        {
            write(1, &s[i][j], 1);
            j++;
        }
        if (s[i + 1])
            write(1, " ", 1);
        i++;    
    }
}
void      ft_print2(char **str)
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
    
    if (!node->data->cmd->args[1])
    {
        write(1, "\n", 1);
        return (0);
    }
    i = check_arg(node->data->cmd->args[1]);
    if (i)
        ft_print(node->data->cmd->args);
    else
    {
        // printf("kan hna\n");
        ft_print2(node->data->cmd->args);
    }
    return (0);
}