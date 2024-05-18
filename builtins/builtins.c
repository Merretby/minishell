/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:31:46 by monachit          #+#    #+#             */
/*   Updated: 2024/05/18 14:36:51 by monachit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_builtins(char *str, t_node *tree)
{
    if (ft_strncmp(str, "echo", 4) == 0)
        return (ft_echo(tree));
    else if (ft_strncmp(str, "cd", 2) == 0)
        return (ft_cd(tree));
    else if (ft_strncmp(str, "pwd", 3) == 0)
        return (ft_pwd(tree));
    else if (ft_strncmp(str, "export", 6) == 0)
        return (ft_export(tree));
    else if (ft_strncmp(str, "unset", 5) == 0)
        return (ft_unset(tree));
    else if (ft_strncmp(str, "env", 3) == 0)
        return (ft_env(tree));
    else if (ft_strncmp(str, "exit", 4) == 0)
        return (ft_exit(tree));
    return (0);
}