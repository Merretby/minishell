/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:54:32 by monachit          #+#    #+#             */
/*   Updated: 2024/07/05 11:58:37 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit2(t_node *node, int fork_flag)
{
	int	nb2;
	int	i;

	i = 0;
	if (node->data->cmd->args[i + 2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	nb2 = ft_atoi(node->data->cmd->args[i + 1]);
	if (nb2 <= -1)
		nb2 = 256 + nb2;
	if (nb2 > 256)
		nb2 = nb2 % 256;
	if (fork_flag == 1)
		printf("exit\n");
	g_v->g_exit_code = nb2;
	exit(nb2);
}

void	ft_exit_norme(t_node *node, int i, int fork_flag)
{
	if (fork_flag == 1)
		printf("exit\n");
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(node->data->cmd->args[i + 1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_v->g_exit_code = 2;
	exit(2);
}

int	ft_exit(t_node *node, int fork_flag)
{
	int	i;

	i = 0;
	if (!node->data->cmd->args[i + 1])
	{
		if (fork_flag == 1)
			printf("exit\n");
		exit(g_v->g_exit_code);
	}
	if (node->data->cmd->args[i + 1])
	{
		if (!ft_isdigit2(node->data->cmd->args[i + 1]))
			ft_exit_norme(node, i, fork_flag);
		else
		{
			if (ft_exit2(node, fork_flag) == 1)
				return (1);
		}
	}
	return (0);
}
