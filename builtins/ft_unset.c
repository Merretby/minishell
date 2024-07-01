/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:00:20 by monachit          #+#    #+#             */
/*   Updated: 2024/06/30 13:33:21 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_findenv(char *env)
{
	int		i;
	char	*key;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = malloc(sizeof(char) * i + 1);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

void	ft_new_env(char *value, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp && tmp->value && strcmp(value, ft_findenv(tmp->value)) == 0)
		{
			tmp->value = NULL;
		}
		tmp = tmp->next;
	}
}

char	**ft_unset(t_node *node, char **env1)
{
	t_env	*env;
	int		i;
	int		j;

	i = 1;
	j = 0;
	env = malloc(sizeof(t_env));
	env->value = env1[0];
	env->next = NULL;
	env = initialize(env, env1);
	while (node->data->cmd->args[i])
	{
		j = 0;
		while (env1[j])
		{
			if (env1[j] && strcmp(node->data->cmd->args[i],
					ft_findenv(env1[j])) == 0)
				ft_new_env(node->data->cmd->args[i], &env);
			j++;
		}
		i++;
	}
	env1 = ft_env1(env1, env);
	return (env1);
}
