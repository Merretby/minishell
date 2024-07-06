/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:27:57 by monachit          #+#    #+#             */
/*   Updated: 2024/07/05 11:47:35 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tokenfile(int copy_fd, int copy_fd2, t_redir *redir)
{
	int	fd;

	fd = open(redir->value, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_dup(copy_fd, copy_fd2);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_v->g_exit_code = 1;
		return (g_v->g_exit_code);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (g_v->g_exit_code);
}

int	ft_tokenoutfile(int copy_fd, int copy_fd2, t_redir *redir)
{
	int	fd;

	fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_dup(copy_fd, copy_fd2);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_v->g_exit_code = 1;
		return (g_v->g_exit_code);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (g_v->g_exit_code);
}

int	token_redir_append(int copy_fd, int copy_fd2, t_redir *redir)
{
	int	fd;

	fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
	{
		ft_dup(copy_fd, copy_fd2);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_v->g_exit_code = 1;
		return (g_v->g_exit_code);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (g_v->g_exit_code);
}

int	ft_redir2(int copy_fd, int copy_fd2, t_redir **redir)
{
	if ((*redir)->type == TOKEN_FILE)
	{
		g_v->g_exit_code = ft_tokenfile(copy_fd, copy_fd2, *redir);
		if (g_v->g_exit_code == 1)
			return (g_v->g_exit_code);
	}
	else if ((*redir)->type == TOKEN_OUTFILE)
	{
		g_v->g_exit_code = ft_tokenoutfile(copy_fd, copy_fd2, *redir);
		if (g_v->g_exit_code == 1)
			return (g_v->g_exit_code);
	}
	else if ((*redir)->type == TOKEN_REDIR_APPEND)
	{
		*redir = (*redir)->next;
		g_v->g_exit_code = token_redir_append(copy_fd, copy_fd2, *redir);
		if (g_v->g_exit_code == 1)
			return (g_v->g_exit_code);
	}
	return (g_v->g_exit_code);
}

int	ft_redir(t_node *tree, char **env1)
{
	t_redir	*redir;
	int		copy_fd;
	int		copy_fd2;

	redir = tree->data->red;
	copy_fd = dup(STDIN_FILENO);
	copy_fd2 = dup(STDOUT_FILENO);
	while (redir)
	{
		if (ft_redir2(copy_fd, copy_fd2, &redir) == 1)
			return (g_v->g_exit_code);
		redir = redir->next;
	}
	ft_execution(tree->left, env1, 1);
	ft_dup(copy_fd, copy_fd2);
	return (g_v->g_exit_code);
}
