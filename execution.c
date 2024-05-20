/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:27:57 by monachit          #+#    #+#             */
/*   Updated: 2024/05/20 17:41:18 by monachit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_execution(t_node *moad)
{
    if (!moad)
        return;

    if (moad->type == CMD)
    {
         if (ft_strncmp(moad->data->cmd->value, "pwd", 3) == 0)
            ft_pwd(moad);
        else if (ft_strncmp(moad->data->cmd->value, "echo", 4) == 0)
            ft_echo(moad);
        else if (ft_strncmp(moad->data->cmd->value, "cd", 2) == 0)
            ft_cd(moad,moad->env1);
        else if (ft_strncmp(moad->data->cmd->value, "export", 6) == 0)
            ft_export(moad);
        else if (ft_strncmp(moad->data->cmd->value, "unset", 5) == 0)
            ft_unset(moad, moad->env1);
        else if (ft_strncmp(moad->data->cmd->value, "env", 3) == 0)
            ft_env(moad);
        else if (ft_strncmp(moad->data->cmd->value, "exit", 4) == 0)
            ft_exit(moad);
    }

    ft_execution(moad->left);
    ft_execution(moad->right);
}