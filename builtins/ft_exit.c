/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:54:32 by monachit          #+#    #+#             */
/*   Updated: 2024/05/31 17:36:53 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_isdigitV2(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]))
            return (1);
        i++;
    }
    return (0);
}
int ft_exit(t_node *node)
{
    int i;

    i = 0;
    if (!node->data->cmd->args[i + 1])
    {
        printf("exit\n");
        exit(g_exit_code);
    }
    if (node->data->cmd->args[i + 1])
    {
        if (!ft_isdigitV2(node->data->cmd->args[i + 1]))
        {
            printf("minishell: exit: %s: numeric argument required\n", node->data->cmd->args[i + 1]);
            printf("exit\n");
            g_exit_code = 0;
            exit(0);
        }
        else
        {
            if (node->data->cmd->args[i + 2])
            {
                printf("minishell: exit: too many arguments\n");
                return (1);
            }
            int nb2 =  ft_atoi(node->data->cmd->args[i + 1]);
            if (nb2 <= -1)
                nb2 = 256 + nb2;
            if (nb2 > 256)
                nb2 = nb2 % 256;
            printf("exit\n");
            g_exit_code = nb2;
            exit(nb2);
        }
    }
    i++;
    return (0);
}
