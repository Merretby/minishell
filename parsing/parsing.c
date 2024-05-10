/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:51:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/09 22:11:26 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("value: %s\n", token->value);
		token = token->next;
	}
}
int  check_erro(t_tree *tree)
{
	while (tree)
	{
		if (ft_strncmp(tree->cmd, "|", 1) == 0 && (tree->right->cmd == NULL || tree->left->cmd == NULL))
		{
			printf("Error: syntax error near unexpected token '|'\n");
			return 1;
		}
		tree = tree->right;
	}
	return 0;
}
void	helper(t_token *token)
{
	t_tree	*tree;

	// join_tokens(token);
	if (token && token->type == TOKEN_PIPE)
	{
		printf("Error: syntax error near unexpected token '|'\n");
		return ;
	}
	tree = create_tree(token);
	if (check_erro(tree))
		return ;
	print_tree(tree);
}
char	*join_cmd(t_token *token)
{
	t_cmd	*cmd;
	char	*tmp;

	if (!token)
		return (NULL);
	cmd = init_cmd(token->value);
	token = token->next;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->prev->helper_flag == 1 || token->prev->helper_flag == 0)
			cmd->cmd = ft_strjoin(cmd->cmd, token->value);
		else if (token->helper_flag == -1)
		{
			cmd->cmd = ft_strjoin(cmd->cmd, " ");
			tmp = cmd->cmd;
			if (token)
			{
				cmd->cmd = ft_strjoin(tmp, token->value);
				free(tmp);
			}
		}
		token = token->next;
	}
	return (cmd->cmd);
}
int	check_pipe(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			i++;
		token = token->next;
	}
	return (i);
}

t_tree	*create_tree(t_token *token)
{
	t_tree	*head;
	t_tree	*tmp;
	int		i;

	head = NULL;
	tmp = NULL;
	i = check_pipe(token);
	if (i != 0)
		head = init_tree("|");
	else
	{
		head = init_tree(join_cmd(token));
		return (head);
	}
	i--;
	tmp = head;
	while (token)
	{
		if (i == 0)
		{
			tmp->left = init_tree(join_cmd(token));
			while (token && token->type != TOKEN_PIPE)
				token = token->next;
			tmp->right = init_tree(join_cmd(token->next));
			break ;
		}
		else if (token->type != TOKEN_PIPE)
		{
			tmp->left = init_tree(join_cmd(token));
			while (token->next->type != TOKEN_PIPE)
				token = token->next;
		}
		else if (token->type == TOKEN_PIPE && i > 0)
		{
			tmp->right = init_tree("|");
			tmp = tmp->right;
			i--;
		}
		token = token->next;
	}
	// print_tree(head);
	return (head);
}
