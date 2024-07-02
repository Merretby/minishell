/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:33:31 by mnachit           #+#    #+#             */
/*   Updated: 2024/07/01 19:44:53 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew2(char *value)
{
	t_env	*new;

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

t_env	*initialize(t_env *env, char **env1)
{
	int	i;

	i = 1;
	while (env1[i])
	{
		ft_lstadd_back2(&env, ft_lstnew2(env1[i]));
		i++;
	}
	return (env);
}
