/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:54:32 by monachit          #+#    #+#             */
/*   Updated: 2024/05/19 20:23:52 by monachit         ###   ########.fr       */
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
        exit(0);
    }
    if (node->data->cmd->args[i + 1] && !node->data->cmd->args[i + 2])
    {
        if (!ft_isdigitV2(node->data->cmd->args[i + 1]))
        {
            int nb = ft_atoi(node->data->cmd->args[i + 1]);

            if (nb > 256)
                nb = nb % 256;
            printf("exit\n");
            printf("minishell: exit: %s: numeric argument required\n", node->data->cmd->args[i + 1]);
            exit(nb);
        }
        else
        {
            int nb2 =  ft_atoi(node->data->cmd->args[i + 1]);
            if (nb2 > 256)
                nb2 = nb2 % 256;
            printf("exit\n");
            exit(nb2);
        }
    }
    else
    {
        printf("exit\n");
        printf("minishell: exit: too many arguments\n");
        return (1);
    }
    i++;
    return (0);
}