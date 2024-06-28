/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:27:57 by monachit          #+#    #+#             */
/*   Updated: 2024/06/28 16:43:46 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void child(char **env1, t_node *tree, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	ft_execution(tree->left, env1, 0);
}

void child2(char **env1, t_node *tree, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_execution(tree->right, env1, 0);
}

int ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int ft_check(t_node *tree)
{
    if (tree->type == PIPE)
        return (1);
    return (0);
}

int	cherch_exit_status(char **args)
{
	int i;
	int j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '$' && args[i][j + 1] == '?')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	expand_exit_status(char **args)
{
	int i;
	int j;
	char *tmp;
	char *tmp2;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '$' && args[i][j + 1] == '?')
			{
				tmp = ft_substr(args[i], 0, j);
				tmp2 = ft_itoa(g_v->g_exit_code);
				args[i] = ft_strjoin(tmp, tmp2);
				free(tmp);
				free(tmp2);
			}
			j++;
		}
		i++;
	}
	g_v->g_exit_code = 0;
}

void ft_wait(int status)
{
	if (WIFEXITED(status))
		g_v->g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_v->g_exit_code = WTERMSIG(status) + 114;
}

int ft_execution(t_node *tree, char **env1, int fork_flag)
{
	if (!tree)
		return (g_v->g_exit_code);
    t_node *tmp;

    tmp = tree;
	signal(SIGINT, signal_handler);
	if (tree->type == CMD)
	{
		if (cherch_exit_status(tree->data->cmd->args))
			expand_exit_status(tree->data->cmd->args);
		if (ft_strcmp(tree->data->cmd->args[0], "pwd") == 0)
			ft_pwd(tree);
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
			ft_exit(tree);
		else
		
			g_v->g_exit_code = ft_execute(tree, env1, fork_flag);
	}
	if (tree->type == PIPE)
	{
		int status;
		int fd[2];
		int ip1;
		int ip2;

		ip1 = 0;
		ip2 = 0;
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
		close(fd[0]);
		close(fd[1]);
		waitpid(ip1, &status, 0);
		waitpid(ip2, &status, 0);
		ft_wait(status);
		signal(SIGINT, signal_handler);
		return (g_v->g_exit_code);
	}
    if (tree->type ==  REDIR)
    {
        t_redir *redir;
        int fd;
        int copy_fd;
		int fd2;
		int copy_fd2;
    
        redir = tree->data->red;
		copy_fd = dup(STDIN_FILENO);
		copy_fd2 = dup(STDOUT_FILENO);
	    while (redir)
	    {
			if(redir->type == TOKEN_FILE)
			{
				
				fd = open(redir->value, O_RDONLY, 0644);
				if (fd == -1)
				{
					dup2(copy_fd, STDIN_FILENO);	
					dup2(copy_fd2, STDOUT_FILENO);
					close(copy_fd2);
					close(copy_fd);
					printf("minishell: %s: No such file or directory\n", redir->value);
					g_v->g_exit_code = 1;
					return (g_v->g_exit_code);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			if (redir->type == TOKEN_OUTFILE)
			{
				fd2 = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd2 == -1)
				{
					dup2(copy_fd, STDIN_FILENO);	
					dup2(copy_fd2, STDOUT_FILENO);
					close(copy_fd2);
					close(copy_fd);					
					printf("minishell: %s: No such file or directory\n", redir->value);
					g_v->g_exit_code = 1;
					return (g_v->g_exit_code);
				}
				dup2(fd2, STDOUT_FILENO);
				close(fd2);
			}
			if (redir->type == TOKEN_REDIR_APPEND)
			{
				redir = redir->next;
				fd2 = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd2 == -1)
				{
					dup2(copy_fd, STDIN_FILENO);	
					dup2(copy_fd2, STDOUT_FILENO);
					close(copy_fd2);
					close(copy_fd);
					printf("minishell: %s: No such file or directory\n", redir->value);
					g_v->g_exit_code = 1;
					return (g_v->g_exit_code);
				}
				dup2(fd2, STDOUT_FILENO);
				close(fd2);
			}
		    redir = redir->next;
        }
		ft_execution(tree->left, env1, 1);
		dup2(copy_fd, STDIN_FILENO);	
		dup2(copy_fd2, STDOUT_FILENO);
		close(copy_fd2);
		close(copy_fd);
	}
	return (g_v->g_exit_code);
}
