/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:58:43 by monachit          #+#    #+#             */
/*   Updated: 2024/05/19 18:17:49 by monachit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	add_env(t_env **env_list, char *env)
// {
// 	t_env	*new;
// 	t_env	*tmp;
// 	char	**env_split;

// 	env_split = ft_split(env, '=');
// 	new = malloc(sizeof(t_env));
// 	new->key = ft_strdup(env_split[0]);
// 	new->value = ft_strdup(env_split[1]);
// 	new->next = NULL;
// 	if (*env_list == NULL)
// 	{
// 		*env_list = new;
// 		new->next = NULL;
// 	}
// 	else
// 	{
// 		tmp = *env_list;
// 		if (tmp)
// 			while (tmp->next)
// 				tmp = tmp->next;
// 		tmp->next = new;
// 	}
// }
// void	print_env(t_env *env)
// {
// 	t_env *tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		printf("tmp--> %s\n	value--> %s\n", tmp->key, tmp->value);
// 		tmp = tmp->next;
// 	}
// }

void	take_env(char **env)
{
	int		i;
	//t_env	*env_list;

	///env_list = NULL;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		//add_env(&env_list, env[i]);
		i++;
	}
	//print_env(env_list);
}
int ft_env(t_node *node)
{
	take_env(node->env1);
	return (0);
}
