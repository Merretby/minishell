/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:51:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/08 17:05:15 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char 	*join_cmd(t_token *token)
{
	t_cmd *cmd;
	char *tmp;

	if (!token)
		return (NULL);
	cmd = init_cmd(token->value);
	token = token->next;
	while (token  && token->type != TOKEN_PIPE)
	{
		cmd->cmd = ft_strjoin(cmd->cmd, " ");
		tmp = cmd->cmd;
		if (token)
		{
			cmd->cmd = ft_strjoin(tmp, token->value);
			free(tmp);
		}
		token = token->next;
	}
	return (cmd->cmd);
}
int check_pipe(t_token *token)
{
	int i;

	i = 0;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			i++;
		token = token->next;
	}
	return (i);
}
void	print_tree(t_tree *tree)
{
	if (tree)
	{
		printf("cmd: %s\n", tree->cmd);
		// printf("right: %s\n", tree->right->cmd);
		// printf("left: %s\n", tree->left->cmd);
		print_tree(tree->left);
		print_tree(tree->right);
	}
}

t_tree			*create_tree(t_token *token)
{
	t_tree *head = NULL;
	t_tree	*tmp = NULL;
	int		i;

	i = check_pipe(token);
	if (i == 1)
	{
		head = init_tree("|");
		head->left = init_tree(join_cmd(token));
		while (token->type != TOKEN_PIPE)
			token = token->next;
		head->right = init_tree(join_cmd(token->next));
		print_tree(head);
		return (head);
	}
	else if (i > 1)
		head = init_tree("|");
	else
		head = init_tree(join_cmd(token));
	i--;
	tmp = head;
	while (token)
	{
		if (token->type == TOKEN_ID && i == 0)
		{
			tmp->right = init_tree(join_cmd(token));
			tmp->left = init_tree(join_cmd(token->prev->prev));
		}
		else if (token->type == TOKEN_ID)
			tmp->left = init_tree(join_cmd(token));
		else if (token->type == TOKEN_PIPE && i > 0)
		 {
			tmp->right = init_tree("|");
			tmp = tmp->right;
			i--;
		}
		token = token->next;
	}
	print_tree(head);
	return (head);
}


// void	print_cmd(t_cmd *cmd)
// {
// 	while (cmd)
// 	{
// 		printf("%s\n", cmd->cmd);
// 		cmd = cmd->next;
// 	}
// }