/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:27:57 by monachit          #+#    #+#             */
/*   Updated: 2024/05/26 14:55:09 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execution(t_node *tree, char **env1)
{
    if (!tree)
        return;

    if (tree->type == CMD)
    {
         if (ft_strncmp(tree->data->cmd->value, "pwd", 3) == 0)
            ft_pwd(tree);
        else if (ft_strncmp(tree->data->cmd->value, "echo", 4) == 0)
            ft_echo(tree);
        else if (ft_strncmp(tree->data->cmd->value, "cd", 2) == 0)
            ft_cd(tree,env1);
        else if (ft_strncmp(tree->data->cmd->value, "export", 6) == 0)
           env1 = ft_export(tree, env1);
        else if (ft_strncmp(tree->data->cmd->value, "unset", 5) == 0)
            env1 = ft_unset(tree, env1);
        else if (ft_strncmp(tree->data->cmd->value, "env", 3) == 0)
            ft_env(env1);
        else if (ft_strncmp(tree->data->cmd->value, "exit", 4) == 0)
            ft_exit(tree);
        else
            ft_execute(tree, env1);
    }

    ft_execution(tree->left, env1);
    ft_execution(tree->right, env1);
}