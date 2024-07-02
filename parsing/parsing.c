/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:51:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/07/02 10:26:47 by moer-ret         ###   ########.fr       */
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

void	list_to_array(t_token *token)
{
	t_args	*tmp;
	t_args	*tmp2;
	int		i;

	i = 0;
	tmp2 = token->args;
	while (tmp2)
	{
		i++;
		tmp2 = tmp2->next;
	}
	token->arg = ft_calloc1(i + 1, sizeof(char *));
	ft_lstadd_back_free(&g_v->adress, init_free(token->arg));
	i = 0;
	tmp = token->args;
	while (tmp)
	{
		token->arg[i] = tmp->args;
		tmp = tmp->next;
		i++;
	}
	token->arg[i] = NULL;
}

void	helper(t_token **token, char **env)
{
	t_node	*tree;
	char	**str;

	str = env;
	if (*token == NULL)
		return ;
	signal(SIGINT, signal_handler);
	heredoc(*token, str);
	if (*retur_nvalue() == 10)
		return ;
	if (parss_command(*token) == 1)
	{
		expand(token, str, 0);
		concatenation_token(*token);
		take_args(*token);
		tree = pipeline(token);
		g_v->g_exit_code = ft_execution(tree, str, 1);
	}
	else
		g_v->g_exit_code = 2;
}

t_redir	*create_redirection(t_token *token)
{
	t_redir	*red;

	red = ft_calloc1(1, sizeof(t_redir));
	ft_lstadd_back_free(&g_v->adress, init_free(red));
	red->value = ft_strdup1(token->value);
	red->type = token->type;
	return (red);
}

t_node	*new_redir(t_token *token)
{
	t_node	*node;

	node = ft_calloc1(1, sizeof(t_node));
	ft_lstadd_back_free(&g_v->adress, init_free(node));
	node->data = ft_calloc1(1, sizeof(t_data));
	ft_lstadd_back_free(&g_v->adress, init_free(node->data));
	node->data->red = ft_calloc1(1, sizeof(t_redir));
	ft_lstadd_back_free(&g_v->adress, init_free(node->data->red));
	node->data->red->value = ft_strdup1(token->value);
	node->data->red->type = token->type;
	node->type = REDIR;
	return (node);
}

t_node	*new_node(t_token *token)
{
	t_node	*node;

	node = ft_calloc1(1, sizeof(t_node));
	ft_lstadd_back_free(&g_v->adress, init_free(node));
	node->data = ft_calloc1(1, sizeof(t_data));
	ft_lstadd_back_free(&g_v->adress, init_free(node->data));
	node->data->cmd = ft_calloc1(1, sizeof(t_cmd));
	ft_lstadd_back_free(&g_v->adress, init_free(node->data->cmd));
	if (token->value)
		node->data->cmd->value = ft_strdup1(token->value);
	else
		node->data->cmd->value = NULL;
	node->data->cmd->type = token->type;
	if (token->args)
		list_to_array(token);
	node->data->cmd->args = token->arg;
	node->data->cmd->ex_flag = token->flag;
	node->type = CMD;
	return (node);
}

t_node	*command(t_token **token)
{
	t_token	*tmp;
	t_token	*tmp2;
	t_node	*node;

	tmp = (*token);
	if ((*token) && ((*token)->type == TOKEN_ID
			|| (*token)->type == TOKEN_STRING))
	{
		tmp2 = (*token);
		*token = (*token)->next;
		node = new_node(tmp2);
		while ((*token) && ((*token)->type == TOKEN_ID
				|| (*token)->type == TOKEN_STRING))
			*token = (*token)->next;
		return (node);
	}
	return (NULL);
}

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
