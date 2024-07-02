/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:44:32 by monachit          #+#    #+#             */
/*   Updated: 2024/07/02 20:10:25 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fined_pwd(char **env)
{
	int		i;
	int		j;
	char	*oldpwd;

	j = 0;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD", 3) == 0)
		{
			while (env[i][j] != '=')
				j++;
			oldpwd = ft_strdup1(&env[i][j + 1]);
			return (oldpwd);
		}
		i++;
	}
	return (NULL);
}

void	change_env(char **env, char *buffer, char *oldpwd)
{
	int		i;
	char	*newpwd;
	char	*oldpwd1;

	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(env[i], "PWD"))
		{
			newpwd = ft_strjoin2("PWD=", buffer);
			env[i] = newpwd;
		}
		if (!ft_strcmp(env[i], "OLDPWD"))
		{
			oldpwd1 = ft_strjoin2("OLDPWD=", oldpwd);
			env[i] = oldpwd1;
		}
		i++;
	}
}

int	ft_cd(t_node *node, char **env)
{
	char	*oldpwd;
	char	buffer[PATH_MAX];

	oldpwd = fined_pwd(env);
	if (node->data->cmd->args[1] == NULL || ft_strncmp(node->data->cmd->args[1],
			"~", 1) == 0)
	{
		g_v->g_exit_code = 0;
		chdir(getenv("HOME"));
	}
	else if (chdir(node->data->cmd->args[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", node->data->cmd->args[1]);
		g_v->g_exit_code = 1;
		return (1);
	}
	getcwd(buffer, PATH_MAX);
	change_env(env, buffer, oldpwd);
	return (0);
}