/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:00:20 by monachit          #+#    #+#             */
/*   Updated: 2024/07/05 10:09:52 by moer-ret         ###   ########.fr       */
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
	ft_lstadd_back_free(&g_v->adress, init_free(key));
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
		if (tmp && tmp->value && ft_strcmp(value, ft_findenv(tmp->value)) == 0)
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
	if (env1[0] == NULL)
		return (env1);
	env = malloc(sizeof(t_env));
	ft_lstadd_back_free(&g_v->adress, init_free(env));
	env->value = env1[0];
	env->next = NULL;
	env = initialize(env, env1);
	while (node->data->cmd->args[i])
	{
		j = 0;
		while (env1[j])
		{
			if (env1[j] && ft_strcmp(node->data->cmd->args[i],
					ft_findenv(env1[j])) == 0)
				ft_new_env(node->data->cmd->args[i], &env);
			j++;
		}
		i++;
	}
	return (env1 = ft_env1(env1, env), env1);
}
