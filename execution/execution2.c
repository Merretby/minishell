/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:50:28 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/02 12:12:54 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_check(t_node *tree)
{
	if (tree->type == PIPE)
		return (1);
	return (0);
}

int	cherch_exit_status(char **args)
{
	int	i;
	int	j;

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
	int		i;
	int		j;
	char	*after;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (args[i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '$' && args[i][j + 1] == '?')
			{
				tmp = ft_substr2(args[i], 0, j);
				after = ft_substr2(args[i], j + 2, ft_strlen(args[i]));
				tmp2 = ft_itoa(g_v->g_exit_code);
				args[i] = ft_strjoin2(tmp, tmp2);
				args[i] = ft_strjoin2(args[i], after);
				free(tmp2);
			}
		}
		i++;
	}
	g_v->g_exit_code = 0;
}
