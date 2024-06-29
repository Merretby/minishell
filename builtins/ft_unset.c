/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:00:20 by monachit          #+#    #+#             */
/*   Updated: 2024/06/29 18:51:01 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env   *ft_lstnew2(char *value)
{
    t_env *new;

    new = malloc(sizeof(t_env));
    ft_lstadd_back_free(&g_v->adress, init_free(new));
    if (!new)
        return (NULL);
    new->value = value;
    new->next = NULL;
    return (new);
}

t_env	*ft_lstlast2(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back2(t_env **lst, t_env *new)
{
	if (lst != NULL && new != NULL)
	{
		if (*lst == NULL)
		{
			*lst = new;
			new->next = NULL;
		}
		else
    		ft_lstlast2(*lst)->next = new;
	}
}

t_env *initialize(t_env *env, char **env1)
{
    int i;

    i = 1;
    while (env1[i])
    {
        ft_lstadd_back2(&env, ft_lstnew2(env1[i]));
        i++;
    }
    return env;
}

char *ft_findEnv(char *env)
{
    int i = 0;
    char *key;

    while (env[i] != '=')
        i++;
    key = malloc(sizeof(char) * i + 1);
    ft_lstadd_back_free(&g_v->adress, init_free(key));
    i = 0;
    while (env[i] != '=')
    {
        key[i] = env[i];
        i++;
    }
    key[i] = '\0';
    return (key);
}

void ft_New_env(char *value, t_env **env)
{
    t_env *tmp;
    tmp = *env;
    while (tmp)
    {
        if (tmp && ft_strcmp(value, ft_findEnv(tmp->value)) == 0)
        {
            tmp->value = NULL;
            // printf("unset %s\n", tmp->next->value);
        }
        tmp = tmp->next;
    }
}

char **ft_unset(t_node *node, char **env1)
{
    t_env *env;
    t_env *to_free;
    int     i = 1;
    int     j = 0;
    
    env = malloc(sizeof(t_env));
    ft_lstadd_back_free(&g_v->adress, init_free(env));
    env->value = env1[0];
    env->next = NULL;
    env = initialize(env, env1);
    while (node->data->cmd->args[i])
    {
        j  = 0;
        while(env1[j])
        {
            if (ft_strcmp(node->data->cmd->args[i], ft_findEnv(env1[j])) == 0)
                ft_New_env(node->data->cmd->args[i], &env);
            j++;
        }
        i++;
    }
    t_env *tmp = env;
    i = 0;
    while (tmp) {
        if (tmp->value)
            env1[i++] = tmp->value;
        to_free = tmp;
        tmp = tmp->next;
        // free(to_free);
    }
    env1[i] = NULL;

    return env1;
}
