/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:52:02 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/05 12:11:57 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_wait(int status)
{
	if (WIFEXITED(status))
		g_v->g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_v->g_exit_code = WTERMSIG(status) + 114;
}

void	pipe_fork(t_node *tree, char **env1, int ip2, int *fd)
{
	ip2 = fork();
	if (ip2 == -1)
		perror("error in fork ip2\n");
	if (ip2 == 0)
	{
		child2(env1, tree, fd);
		exit(g_v->g_exit_code);
	}
}

int	pipe_execution(t_node *tree, char **env1, int ip1, int ip2)
{
	int	status;
	int	fd[2];

	if (pipe(fd) == -1)
		exit(1);
	ip1 = fork();
	if (ip1 == -1)
		perror("error in fork ip1");
	signal(SIGINT, signal_handler_2);
	if (ip1 == 0)
	{
		child(env1, tree, fd);
		exit(g_v->g_exit_code);
	}
	if (ip1 != 0)
		pipe_fork(tree, env1, ip2, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(ip1, &status, 0);
	waitpid(ip2, &status, 0);
	ft_wait(status);
	signal(SIGINT, signal_handler);
	return (g_v->g_exit_code);
}

int	cmd_execution(t_node *tree, char **env1, int fork_flag, char *s)
{
	signal(SIGINT, signal_handler);
	if (cherch_exit_status(tree->data->cmd->args))
		expand_exit_status(tree->data->cmd->args);
	if (ft_strcmp(tree->data->cmd->args[0], "pwd") == 0)
		ft_pwd(tree, s);
	else if (ft_strcmp(tree->data->cmd->args[0], "echo") == 0)
		ft_echo(tree);
	else if (ft_strcmp(tree->data->cmd->args[0], "cd") == 0)
		ft_cd(tree, env1);
	else if (ft_strcmp(tree->data->cmd->args[0], "export") == 0)
		env1 = ft_export(tree, env1);
	else if (ft_strcmp(tree->data->cmd->args[0], "unset") == 0)
		env1 = ft_unset(tree, env1);
	else if (ft_strcmp(tree->data->cmd->args[0], "env") == 0)
		ft_env(env1);
	else if (ft_strcmp(tree->data->cmd->args[0], "exit") == 0)
		ft_exit(tree, fork_flag);
	else if (ft_strcmp(tree->data->cmd->args[0], "/\0") == 0)
	{
		ft_putendl_fd("minishell: /: Is a directory", 2);
		g_v->g_exit_code = 126;
	}
	else
		g_v->g_exit_code = ft_execute(tree, env1, fork_flag);
	return (g_v->g_exit_code);
}

int	ft_execution(t_node *tree, char **env1, int fork_flag)
{
	t_node	*tmp;
	char	buffer[PATH_MAX];
	char	buffer2[PATH_MAX];

	if (!tree)
		return (g_v->g_exit_code);
	tmp = tree;
	if (tree->type == CMD)
	{
		getcwd(buffer, PATH_MAX);
		if (!buffer[0])
			ft_strcpy(buffer, buffer2);
		else
			getcwd(buffer2, PATH_MAX);
		g_v->g_exit_code = cmd_execution(tree, env1, fork_flag, buffer);
	}
	if (tree->type == PIPE)
		g_v->g_exit_code = pipe_execution(tree, env1, 0, 0);
	if (tree->type == REDIR)
		g_v->g_exit_code = ft_redir(tree, env1);
	return (g_v->g_exit_code);
}
