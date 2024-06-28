/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:46:16 by mnachit           #+#    #+#             */
/*   Updated: 2024/06/28 17:37:49 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_free	*init_free(void *content)
{
	t_free	*new;

	if (!content)
		return (NULL);
	new = (t_free *)malloc(sizeof(t_free));
	if (!new)
		return (NULL);
	new->adress = content;
	new->next = NULL;
	return (new);
}

t_free	*ft_lstlast_free(t_free *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_free(t_free **lst, t_free *new)
{
	t_free	*tmp;

	if (lst != NULL && new != NULL)
	{
		if (*lst == NULL)
		{
			*lst = new;
			new->next = NULL;
		}
		else
		{
			tmp = ft_lstlast_free(*lst);
			ft_lstlast_free(*lst)->next = new;
		}
	}

}

void	ft_lstclear_free(t_free **lst)
{
	t_free	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->adress);
		free(tmp);
	}
	*lst = NULL;
}

void	ft_free(t_token **token, t_lexer **lexer)
{
	// t_token	*head;
	t_token	*tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		free(tmp);
	}
	*token = NULL;
	*lexer = NULL;
}

void	free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}