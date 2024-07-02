/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:54:32 by monachit          #+#    #+#             */
/*   Updated: 2024/07/02 05:58:43 by mnachit          ###   ########.fr       */
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

int	ft_exit2(t_node *node)
{
	int	nb2;
	int	i;

	i = 0;
	if (node->data->cmd->args[i + 2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	nb2 = ft_atoi(node->data->cmd->args[i + 1]);
	if (nb2 <= -1)
		nb2 = 256 + nb2;
	if (nb2 > 256)
		nb2 = nb2 % 256;
	printf("exit\n");
	g_v->g_exit_code = nb2;
	exit(nb2);
}

int	ft_exit(t_node *node)
{
	int	i;

	i = 0;
	if (!node->data->cmd->args[i + 1])
	{
		printf("exit\n");
		exit(g_v->g_exit_code);
	}
	if (node->data->cmd->args[i + 1])
	{
		if (!ft_isdigit2(node->data->cmd->args[i + 1]))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				node->data->cmd->args[i + 1]);
			printf("exit\n");
			g_v->g_exit_code = 0;
			exit(0);
		}
		else
		{
			if (ft_exit2(node) == 1)
				return (1);
		}
	}
	return (0);
}
