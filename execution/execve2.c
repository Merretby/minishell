/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:49:14 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/05 11:16:26 by moer-ret         ###   ########.fr       */
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
		exit(127);
	}
	if (ft_strncmp(tree->data->cmd->args[0], "/nfs", 4) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tree->data->cmd->args[0], 2);
		ft_putstr_fd(": Is a directory \n", 2);
		exit(126);
	}
}

void	case2(t_node *tree, char **env)
{
	if (access(tree->data->cmd->args[0], F_OK | X_OK) == 0)
	{
		if (execve(tree->data->cmd->args[0], tree->data->cmd->args, env) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tree->data->cmd->args[0], 2);
			ft_putstr_fd(" command not found\n", 2);
			exit(127);
		}
	}
	else
	{
		write(2, "minishell: ", 11);
		perror(tree->data->cmd->value);
		exit(127);
	}
	if (ft_strncmp(tree->data->cmd->args[0], "/nfs", 4) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tree->data->cmd->args[0], 2);
		ft_putstr_fd(": Is a directory \n", 2);
		exit(126);
	}
}

void	ft_dup(int copy_fd, int copy_fd2)
{
	dup2(copy_fd, STDIN_FILENO);
	dup2(copy_fd2, STDOUT_FILENO);
	close(copy_fd2);
	close(copy_fd);
}
