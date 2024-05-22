/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:44:32 by monachit          #+#    #+#             */
/*   Updated: 2024/05/21 17:24:47 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *fined_pwd(char **env)
{
    int i;
    int j;
    char *oldPwd;

    j = 0;
    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "PWD", 3) == 0)
        {
            while(env[i][j] != '=')
                j++;
            oldPwd = ft_strdup(&env[i][j + 1]);
            return (oldPwd);
        }
        i++;
    }
    return (NULL);
}

void    change_env(char **env, char *buffer, char *oldPwd)
{
    int i;
    char *newPwd;
    char *oldPwd1;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "PWD", 3) == 0)
        {
            newPwd = ft_strjoin("PWD=", buffer);
            env[i] = newPwd;
        }
        if (ft_strncmp(env[i], "OLDPWD", 6) == 0)
        {
            oldPwd1 = ft_strjoin("OLDPWD=", oldPwd);
            env[i] = oldPwd1;
        }
        i++;
    }
}

int     ft_cd(t_node *node, char **env)
{
    char *oldPwd;

    oldPwd = fined_pwd(env);
    if (node->data->cmd->args[1] == NULL || ft_strncmp(node->data->cmd->args[1] , "~", 1) == 0)
    {
        printf("cd: HOME not set\n");
        chdir(getenv("HOME"));
    }
    else if (chdir(node->data->cmd->args[1]) == -1)
    {
        printf("cd: %s: No such file or directory\n", node->data->cmd->args[1]);
        return (1);
    }
    char buffer[PATH_MAX];
    getcwd(buffer, PATH_MAX);
    change_env(env, buffer, oldPwd);
    return (0);
}