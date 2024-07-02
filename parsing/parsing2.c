/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:01:00 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/02 11:01:08 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	concatenation_token2(t_token **token, t_token **next)
{
	char	*concatenated;

	concatenated = ft_strjoin2((*token)->value, (*next)->value);
	(*token)->value = concatenated;
	(*token)->helper_flag = (*token)->next->helper_flag;
	(*token)->next = (*next)->next;
}

void	concatenation_token(t_token *token)
{
	t_token	*tmp;
	t_token	*next;

	if (token == NULL)
		return ;
	tmp = token;
	while (token)
	{
		if (token->helper_flag == 1)
		{
			next = token->next;
			while (next && (next->type == TOKEN_ID
					|| next->type == TOKEN_STRING))
			{
				concatenation_token2(&token, &next);
				next = token->next;
				if (token->helper_flag == 0)
					break ;
			}
		}
		token = token->next;
	}
}

void	add_to_args(t_token *token, char *str)
{
	t_args	*new;
	t_args	*tmp;

	if (token == NULL)
		return ;
	new = ft_calloc1(1, sizeof(t_args));
	ft_lstadd_back_free(&g_v->adress, init_free(new));
	new->args = str;
	new->next = NULL;
	if (token->args == NULL)
		token->args = new;
	else
	{
		tmp = token->args;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	delete_node(t_token **head, t_token *node)
{
	t_token	*tmp;

	tmp = (*head);
	if (tmp == node)
	{
		(*head) = node->next;
		node = NULL;
	}
	else
	{
		node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		node = NULL;
	}
}

void	take_args(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp2;

	if (token == NULL)
		return ;
	while (token)
	{
		if (token->type == TOKEN_ID || token->type == TOKEN_STRING)
		{
			tmp = token;
			while (token && (token->type == TOKEN_ID
					|| token->type == TOKEN_STRING))
			{
				add_to_args(tmp, token->value);
				tmp2 = token;
				token = token->next;
				while (token && (token->type != TOKEN_ID && \
					token->type != TOKEN_STRING && token->type != TOKEN_PIPE))
					token = token->next;
			}
		}
		if (token)
			token = token->next;
	}
}
