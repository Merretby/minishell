/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:21:17 by moer-ret          #+#    #+#             */
/*   Updated: 2024/06/07 11:43:32 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	case1(char *tmp, t_node *tree, char **env)
{
	if (execve(tmp, tree->data->cmd->args, env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tree->data->cmd->args[0], 2);
		ft_putstr_fd(" command not found\n", 2);
		exit(1);
	}
}

void	case2(t_node *tree, char **env)
{
	if (access(tree->data->cmd->args[0], F_OK | X_OK) == 0)
		execve(tree->data->cmd->args[0], tree->data->cmd->args, env);
	else
	{
		write(2, "minishell: ", 11);
		perror(tree->data->cmd->value);
		exit(1);
	}
}

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

void	ft_execute2(t_node *tree, char **env)
{
	char	*str;
	char	**path;
	char   *tmp;
	int		i;

	i = 0;

	str = path_check(env);
	if (str == NULL)
		exit(1);
	path = ft_split(str + 5, ':');
	while (path[i] && tree->data->cmd->args)
	{
		if (ft_strchr(tree->data->cmd->args[0], '/') == NULL)
		{
			str = ft_strjoin("/", tree->data->cmd->args[0]);
			tmp = ft_strjoin(path[i], str);
			free (str);
			if (access(tmp, F_OK) == 0)
				break ;
			free(tmp);
		}
		else
		{
			case2(tree, env);
			break ;
		}
		i++;
	}
	if (ft_strchr(tree->data->cmd->args[0], '/') == NULL)
		case1(tmp, tree, env);
}

int	 ft_execute(t_node *tree,  char **env, int fork_flag)
{
	int ip1;
	int	status;

	if (fork_flag == 0)
	{
		ft_execute2(tree, env);
		return 0;
	}
	else if (fork_flag == 1)
	{
		ip1 = fork();
		if (ip1 == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			ft_execute2(tree, env);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				g_exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_code = WTERMSIG(status) + 128;
		}
	}
	return (g_exit_code);
}