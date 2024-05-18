/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:44:32 by monachit          #+#    #+#             */
/*   Updated: 2024/05/18 14:36:56 by monachit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *fined_pwd(t_env    *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, "PWD", 3) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

void    change_env(t_env **env, char *buffer, char *oldPwd)
{
    t_env *tmp;

    tmp = *env;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, "PWD", 3) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(buffer);
        }
        if (ft_strncmp(tmp->key, "OLDPWD", 6) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(oldPwd);
        }
        tmp = tmp->next;
    }
}
int     ft_cd(t_node *node)
{
    char *oldPwd;

    oldPwd = fined_pwd(node->env);
    if (chdir(node->data->cmd->args[1]) == -1)
    {
        printf("cd: %s: No such file or directory\n", node->data->cmd->args[1]);
        return (1);
    }
    char buffer[PATH_MAX];
    getcwd(buffer, PATH_MAX);
    change_env(&node->env, buffer, oldPwd);
    return (0);
}