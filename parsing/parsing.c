/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:51:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/14 18:00:51 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void   print_tree(t_node *tree)
{
	if(tree == NULL)
		return;
	printf("%s\n", tree->token->value);
	print_tree(tree->left);
	print_tree(tree->right);
}

void    helper(t_token *token)
{
	t_node *tree;

	if (token == NULL)
		return ;
	tree = pipeline(&token);
	print_tree(tree);
}

t_node *new_node(t_token *token)
{
	t_node *new = malloc(sizeof(t_node));
	new->token = token;
	new->left = NULL;
	new->right = NULL;
	return new;
}

t_node *command(t_token **token)
{
	t_node *new;
	
	if((*token)->type == TOKEN_ID || (*token)->type == TOKEN_STRING\
		|| (*token)->type == TOKEN_DOLLAR)
	{
		new = new_node(*token);
		*token = (*token)->next;
		return new;
	}
	else
	{
		*token = (*token)->next;
		return (NULL);
	}
	return NULL;
}

t_node  *pipeline(t_token **token)
{
	t_node *left;
	t_node *new;

	left = rederiction(token);
	while((*token) && (*token)->type == TOKEN_PIPE)
	{
		new = new_node(*token);
		*token = (*token)->next;
		new->left = left;
		new->right = pipeline(token);
		left = new;
	}
	return left;
}

t_node	*rederiction(t_token **token)
{
	t_node *left;
	t_node *new;

	left = command(token);
	while((*token) && ((*token)->type == TOKEN_REDIR_IN ||\
	 (*token)->type == TOKEN_REDIR_OUT ||\
	 (*token)->type == TOKEN_REDIR_APPEND ||\
	 (*token)->type == TOKEN_OUTFILE ||\
	(*token)->type == TOKEN_FILE))
	{
		new = new_node(*token);
		(*token) = (*token)->next;
		new->left = left;
		new->right = rederiction(token);
		left = new;
	}
	return left;
}