/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:44:23 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/26 15:14:18 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	case1(char *tmp, t_node *tree, char **env, char **path)
{
	if (execve(tmp, tree->data->cmd->args, env) == -1)
		printf("minishell: command not found\n");
}

void	case2(t_node *tree, char **env, char **path)
{
	if (access(tree->data->cmd->args[0], F_OK | X_OK) == 0)
		execve(tree->data->cmd->args[0], tree->data->cmd->args, env);
	else
		printf("minishell: command not found\n");
}

char	*path_check(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
    
	return (env[i]);
}

void ft_execute2(t_node *tree, char **env)
{
    char	*str;
	char	**path;
    char   *tmp;
	int		i;

	i = 0;
	str = path_check(env);
	path = ft_split(str + 5, ':');
    
	while (path[i] && tree->data->cmd->args)
	{
		if (ft_strchr(tree->data->cmd->args[0], '/') == NULL) ///nfs/homes/moer-ret/bin  /usr/local/sbin /usr/local/bin /usr/sbin /usr/bin /sbin /bin /usr/games /ls
		{
			str = ft_strjoin("/", tree->data->cmd->args[0]);
			tmp = ft_strjoin(path[i], str);
			free (str);
			if (access(tmp, F_OK) == 0)
				break ;
			free(tmp);
		}
		else
			case2(tree, env, path);
		i++;
	}
	if (ft_strchr(tree->data->cmd->args[0], '/') == NULL)
		case1(tmp, tree, env, path);
}

void	ft_execute(t_node *tree,  char **env)
{   
    // int fd[2];
    int ip1;

    // if (pipe(fd) == -1)
    //     printf("error\n");
    ip1 = fork();
    if (ip1 == 0)
    {
        ft_execute2(tree, env);
    }
    else
    {
        waitpid(ip1, NULL, 0);
    }
}