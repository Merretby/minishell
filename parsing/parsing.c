/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:51:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/07/04 18:19:45 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	helper(t_token **token, char **env)
{
	t_node	*tree;
	char	**str;

	str = env;
	if (*token == NULL)
		return ;
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
