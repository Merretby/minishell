/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:03:19 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/02 11:03:25 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*new_pipe(t_token *token)
{
	t_node	*node;

	node = ft_calloc1(1, sizeof(t_node));
	ft_lstadd_back_free(&g_v->adress, init_free(node));
	node->data = ft_calloc1(1, sizeof(t_data));
	ft_lstadd_back_free(&g_v->adress, init_free(node->data));
	node->data->pipe = ft_calloc1(1, sizeof(t_pipe));
	ft_lstadd_back_free(&g_v->adress, init_free(node->data->pipe));
	node->data->pipe->value = ft_strdup1(token->value);
	node->data->pipe->type = token->type;
	node->type = PIPE;
	return (node);
}

t_node	*pipeline(t_token **token)
{
	t_node	*left;
	t_node	*new;

	if (token == NULL)
		return (NULL);
	left = rederiction(token);
	while ((*token) && (*token)->type == TOKEN_PIPE)
	{
		new = new_pipe(*token);
		new->type = PIPE;
		*token = (*token)->next;
		new->left = left;
		new->right = pipeline(token);
		left = new;
	}
	return (left);
}

void	redir2(t_token **token, t_node **left)
{
	t_token	*tmp_token;

	tmp_token = *token;
	while (tmp_token && (tmp_token->type == TOKEN_REDIR_IN
			|| tmp_token->type == TOKEN_REDIR_OUT
			|| tmp_token->type == TOKEN_REDIR_APPEND
			|| tmp_token->type == TOKEN_OUTFILE
			|| tmp_token->type == TOKEN_FILE))
	{
		tmp_token = tmp_token->next;
	}
	if (tmp_token && (tmp_token->type == TOKEN_ID
			|| tmp_token->type == TOKEN_STRING))
		*left = new_node(tmp_token);
}

void	redir3(t_redir **tmp, t_token **token)
{
	while ((*token) && ((*token)->type == TOKEN_REDIR_IN
			|| (*token)->type == TOKEN_REDIR_OUT
			|| (*token)->type == TOKEN_REDIR_APPEND
			|| (*token)->type == TOKEN_OUTFILE || (*token)->type == TOKEN_FILE))
	{
		(*tmp)->next = create_redirection(*token);
		*tmp = (*tmp)->next;
		(*token) = (*token)->next;
		if ((*token) && ((*token)->type == TOKEN_ID
				|| (*token)->type == TOKEN_STRING))
			(*token) = (*token)->next;
	}
}

t_node	*rederiction(t_token **token)
{
	t_node	*left;
	t_node	*node;
	t_redir	*tmp;

	left = command(token);
	if (left == NULL)
		redir2(token, &left);
	if ((*token) && ((*token)->type == TOKEN_REDIR_IN
			|| (*token)->type == TOKEN_REDIR_OUT
			|| (*token)->type == TOKEN_REDIR_APPEND))
	{
		node = new_redir(*token);
		tmp = node->data->red;
		(*token) = (*token)->next;
		redir3(&tmp, token);
		node->left = left;
		left = node;
	}
	return (left);
}
