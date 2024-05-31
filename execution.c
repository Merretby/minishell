/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:27:57 by monachit          #+#    #+#             */
/*   Updated: 2024/05/31 15:35:07 by mnachit          ###   ########.fr       */
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

void ft_execution(t_node *tree, char **env1, int fork_flag)
{
	if (!tree)
		return;
    t_node *tmp;

    tmp = tree;
	if (tree->type == CMD)
	{
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
			ft_execute(tree, env1, fork_flag);
	}
	if (tree->type == PIPE)
	{
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
		return;
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
				
				fd = open(redir->value, O_RDONLY);
				if (fd == -1)
				{
					printf("minishell: %s: No such file or directory\n", redir->value);
					return;
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			if (redir->type == TOKEN_OUTFILE)
			{
				fd2 = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd2 == -1)
				{
					printf("minishell: %s: No such file or directory\n", redir->value);
					return;
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
					printf("minishell: %s: No such file or directory\n", redir->value);
					return;
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
}
//nuildtins
// < in dup
//after exec
//int original_stdin = dup(STDIN_FILENO;
//dup2(original_stdin, STDIN_FILENO);

// not builtins
//fork
// redirection_handling();            < in cat

//fd  = open (file, O_RDONLY | O_CREAT | O_TRUNC, 0644);
//dup2(fd, 0);


