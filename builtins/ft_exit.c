/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:54:32 by monachit          #+#    #+#             */
/*   Updated: 2024/05/31 16:01:53 by moer-ret         ###   ########.fr       */
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
    if (!node->data->cmd->args[i])
    {
        printf("exit\n");
        exit(0);
    }
    if (node->data->cmd->args[i] && !node->data->cmd->args[i + 1])
    {
        if (!ft_isdigitV2(node->data->cmd->args[i]))
        {
            int nb = ft_atoi(node->data->cmd->args[i]);

            if (nb > 256)
                nb = nb % 256;
            printf("exit\n");
            printf("minishell: exit: %s: numeric argument required\n", node->data->cmd->args[i]);
            exit(nb);
        }
        else
        {
            int nb2 =  ft_atoi(node->data->cmd->args[i]);
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