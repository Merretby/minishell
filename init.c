/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:57:56 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/12 15:22:04 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*init_tree(t_token *token)
{
	t_tree	*new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->red = NULL;
	new->type = token->type;
	new->value = token->value;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_cmd	*init_cmd(t_token *token)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = token->value;
	new->args = NULL;
	new->type =token->type;
	new->next = NULL;
	return (new);
}

// t_pipe	*init_pipe(t_cmd *cmd)
// {
// 	t_pipe	*new;

// 	new = malloc(sizeof(t_pipe));
// 	if (!new)
// 		return (NULL);
// 	new->cmd = cmd;
// 	new->next = NULL;
// 	return (new);
// }

t_redir	*init_redir(t_token *token)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->value = token->value;
	new->type = token->type;
	new->next = NULL;
	return (new);
}