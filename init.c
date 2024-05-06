/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:57:56 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/06 16:58:30 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*init_tree(char *cmd)
{
	t_tree *new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_cmd	*init_cmd(char *cmd)
{
	t_cmd *new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->next = NULL;
	return (new);
}

t_pipe	*init_pipe(t_cmd *cmd)
{
	t_pipe *new;

	new = malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->next = NULL;
	return (new);
}

t_redir	*init_redir(t_pipe *pipe)
{
	t_redir *new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->pipe = pipe;
	new->next = NULL;
	return (new);
}