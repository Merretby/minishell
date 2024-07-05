/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:21:17 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/05 10:49:50 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_check(char **env)
{
	int	i;

	i = 0;
	if (env == NULL)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (env[i]);
}

void	ft_execute2(t_node *tree, char **env, int i)
{
	char	*str;
	char	**path;
	char	*tmp;

	str = path_check(env);
	if (str == NULL)
		case2(tree, env);
	path = ft_split1(str + 5, ':');
	while (path[++i] && tree->data->cmd->args)
	{
		if (ft_strchr(tree->data->cmd->args[0], '/') == NULL)
		{
			str = ft_strjoin2("/", tree->data->cmd->args[0]);
			tmp = ft_strjoin2(path[i], str);
			if (access(tmp, F_OK) == 0)
				break ;
		}
		else
		{
			case2(tree, env);
			break ;
		}
	}
	if (ft_strchr(tree->data->cmd->args[0], '/') == NULL)
		case1(tmp, tree, env);
}

void	ft_execute_norme(t_node *tree, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_execute2(tree, env, -1);
	exit(127);
}

void	ft_execute_norme2(int status)
{
	if (WIFEXITED(status))
		g_v->g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_v->g_exit_code = WTERMSIG(status) + 128;
}

int	ft_execute(t_node *tree, char **env, int fork_flag)
{
	int	ip1;
	int	status;

	signal(SIGINT, signal_handler_2);
	signal(SIGQUIT, signal_quit);
	if (fork_flag == 0)
	{
		ft_execute2(tree, env, -1);
		return (g_v->g_exit_code);
	}
	else if (fork_flag == 1)
	{
		ft_check_mini(tree);
		ip1 = fork();
		if (ip1 == 0)
			ft_execute_norme(tree, env);
		else
		{
			wait(&status);
			ft_execute_norme2(status);
		}
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	return (g_v->g_exit_code);
}
