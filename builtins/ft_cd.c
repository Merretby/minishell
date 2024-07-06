/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:44:32 by monachit          #+#    #+#             */
/*   Updated: 2024/07/05 12:44:23 by moer-ret         ###   ########.fr       */
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

char	*new_env(char *env)
{
	int		i;
	char	*new_env;

	i = 0;
	if (env == NULL)
		return (NULL);
	while (env[i] != '=')
		i++;
	new_env = ft_strdup1(env);
	new_env[i] = '\0';
	return (new_env);
}

void	change_env(char **env, char *buffer, char *oldpwd)
{
	int		i;
	char	*newpwd;
	char	*oldpwd1;

	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(new_env(env[i]), "PWD"))
		{
			newpwd = ft_strjoin2("PWD=", buffer);
			env[i] = newpwd;
		}
		if (!ft_strcmp(new_env(env[i]), "OLDPWD"))
		{
			oldpwd1 = ft_strjoin2("OLDPWD=", oldpwd);
			env[i] = oldpwd1;
		}
		i++;
	}
}

char	*get_env(char **env, int len)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (!ft_strcmp("HOME", new_env(env[i])))
		{
			j = len;
			break ;
		}
		i++;
	}
	tmp = ft_substr2(env[i], j, ft_strlen(env[i]) - j);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

int	ft_cd(t_node *node, char **env)
{
	char	*oldpwd;
	char	buffer[PATH_MAX];

	oldpwd = fined_pwd(env);
	if (node->data->cmd->args[1] && node->data->cmd->args[2])
		return (g_v->g_exit_code = 1, ft_putstr_fd("cd: too many arguments\n",
				2), 1);
	if (!ft_strcmp(node->data->cmd->args[1], "\0"))
		return (0);
	if (node->data->cmd->args[1] == NULL || ft_strcmp(node->data->cmd->args[1],
			"~") == 0)
	{
		g_v->g_exit_code = 0;
		if (ft_check_cd(env) == 1)
			return (g_v->g_exit_code = 1, 1);
	}
	else if (chdir(node->data->cmd->args[1]) == -1)
	{
		error_cd(node->data->cmd->args[1]);
		return (g_v->g_exit_code = 1, 1);
	}
	getcwd(buffer, PATH_MAX);
	change_env(env, buffer, oldpwd);
	return (0);
}
