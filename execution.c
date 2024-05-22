/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:27:57 by monachit          #+#    #+#             */
/*   Updated: 2024/05/22 13:28:08 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execution(t_node *tree)
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
            ft_cd(tree,tree->env1);
        else if (ft_strncmp(tree->data->cmd->value, "export", 6) == 0)
           tree->env1 = ft_export(tree, tree->env1);
        else if (ft_strncmp(tree->data->cmd->value, "unset", 5) == 0)
            tree->env1 = ft_unset(tree, tree->env1);
        else if (ft_strncmp(tree->data->cmd->value, "env", 3) == 0)
            ft_env(tree);
        else if (ft_strncmp(tree->data->cmd->value, "exit", 4) == 0)
            ft_exit(tree);
    }

    ft_execution(tree->left);
    ft_execution(tree->right);
}