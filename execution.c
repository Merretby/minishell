/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:27:57 by monachit          #+#    #+#             */
/*   Updated: 2024/05/31 15:10:19 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(char **env1, t_node *tree, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	ft_execution(tree->left, env1, 0);
}

void	child2(char **env1, t_node *tree, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_execution(tree->right, env1, 0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-2);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void ft_execution(t_node *tree, char **env1, int fork_flag)
{
	if (!tree)
		return;
	
	if (tree->type == CMD)
	{
		 if (ft_strcmp(tree->data->cmd->value, "pwd") == 0)
			ft_pwd(tree);
		else if (ft_strcmp(tree->data->cmd->value, "echo") == 0)
			ft_echo(tree);
		else if (ft_strcmp(tree->data->cmd->value, "cd") == 0)
			ft_cd(tree,env1);
		else if (ft_strcmp(tree->data->cmd->value, "export") == 0)
		   env1 = ft_export(tree, env1);
		else if (ft_strcmp(tree->data->cmd->value, "unset") == 0)
			env1 = ft_unset(tree, env1);
		else if (ft_strcmp(tree->data->cmd->value, "env") == 0)
			ft_env(env1);
		else if (ft_strcmp(tree->data->cmd->value, "exit") == 0)
			ft_exit(tree);
		else
			ft_execute(tree, env1, fork_flag);
	}
	if (tree->type == PIPE)
	{
		int		fd[2];
		int		ip1;
		int		ip2;
	
		ip1 = 0;
		ip2 = 0;
		if (pipe(fd) == -1)
			exit (1);
		ip1 = fork();
		if (ip1 == -1)
			perror("error in fork ip1");
		if (ip1 == 0)
		{
			child(env1, tree, fd);
			exit(1);
		}
		if (ip1 != 0)
		{
			ip2 = fork();
			if (ip2 == -1)
				perror("error in fork ip2\n");
			if (ip2 == 0)
			{
				child2(env1, tree, fd);
				exit(1);
			}
		}
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
		wait(NULL);
		return ;
	}
}
