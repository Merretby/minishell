/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:32:13 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/02 17:05:25 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstlast1(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back1(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (lst != NULL && new != NULL)
	{
		if (*lst == NULL)
		{
			*lst = new;
			new->next = NULL;
			new->prev = NULL;
		}
		else
		{
			tmp = ft_lstlast1(*lst);
			ft_lstlast1(*lst)->next = new;
			new->prev = tmp;
		}
	}
}

t_redir	*ft_lstlast_red(t_redir *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_last_back_red(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (lst != NULL && new != NULL)
	{
		if (*lst == NULL)
		{
			*lst = new;
			new->next = NULL;
		}
		else
		{
			tmp = ft_lstlast_red(*lst);
			tmp->next = new;
			new->next = NULL;
		}
	}
}

void	init_global(void)
{
	g_v = (t_g_var *)malloc(sizeof(t_g_var));
	g_v->adress = NULL;
	g_v->g_exit_code = 0;
}
