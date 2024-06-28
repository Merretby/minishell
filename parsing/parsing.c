/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:51:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/06/28 23:36:57 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void print_redir(t_redir*red)
{
	while (red)
	{
		printf("redirection--> %s\n", red->value);
		red = red->next;
	}
}

void   print_tree(t_node *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type == PIPE)
	{
		printf("PIPE: %s\n", tree->data->pipe->value);
	}
	else if (tree->type == CMD)
	{
		// if (tree->data->cmd->value != NULL)
		printf("CMD: %s\n", tree->data->cmd->value);
		if (tree->data->cmd->args != NULL)
		{
			for (int i = 0; tree->data->cmd->args[i]; i++)
				printf("args[%d]: %s, flag: %d\n", i, tree->data->cmd->args[i], tree->data->cmd->ex_flag);
		}
	}
	else if (tree->type == REDIR)
	{
		if (tree->data->red->value != NULL)
		{
			printf("REDIR: %s\n", tree->data->red->value);
			print_redir(tree->data->red);
		}
		
	}
	print_tree(tree->left);
	print_tree(tree->right);
}

void	concatenation_token(t_token *token)
{
	t_token *tmp;
	t_token *next;
	char *concatenated;
	
	if (token == NULL)
		return ;
	tmp = token;
	while (token)
	{
		if (token->helper_flag == 1)
		{
			next = token->next;
			while (next && (next->type == TOKEN_ID || next->type == TOKEN_STRING))
			{
				concatenated = ft_strjoin2(token->value, next->value);
				// free(token->value);
				token->value = concatenated;
				token->helper_flag = token->next->helper_flag;
				token->next = next->next;
				// free(next->value);
				// free(next);
				next = token->next;
				if (token->helper_flag == 0)
					break ;
			}
		}
		token = token->next;
	}
}

void add_to_args(t_token *token, char *str)
{
	t_args *new;
	t_args *tmp;

	if (token == NULL)
		return ;
	new = ft_calloc1 (1, sizeof(t_args));
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

void delete_node(t_token **head, t_token *node)
{
	t_token *tmp;
	
	tmp = (*head);
	if (tmp == node)
	{
		(*head) = node->next;
		// free(node->value);
		// free(node);
		node = NULL;
	}
	else
	{
	
		node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		// free(node->value);
		// free(node);
		node = NULL;
	}
}

void	take_args(t_token *token)
{
	t_token *tmp;
	t_token *head;
	t_token *tmp2;

	if (token == NULL)
		return ;
	head = token;
	while (token)
	{
		if (token->type == TOKEN_ID || token->type == TOKEN_STRING)
		{
			tmp = token;
			while (token && (token->type == TOKEN_ID || token->type == TOKEN_STRING))
			{
				add_to_args(tmp, token->value);
				tmp2 = token;
				token = token->next;
				while (token && (token->type != TOKEN_ID && token->type != TOKEN_STRING &&\
				 token->type != TOKEN_PIPE))
					token = token->next;
			}
		}
		if (token)
			token = token->next;
	}
}

void	list_to_array(t_token *token)
{
	t_args *tmp;
	t_args *tmp2;
	int i;
	
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

void	free_redir(t_redir *red)
{
	t_redir *tmp;
	
	while (red)
	{
		tmp = red;
		red = red->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_args(char **args)
{
	int i = 0;
	
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_tree(t_node *tree)
{
	// int i = 0;
	
	if (tree == NULL)
		return ;
	if (tree->type == CMD)
	{
		if (tree->data->cmd->value)
			free(tree->data->cmd->value);
		if (tree->data->cmd->args)
		{
			// while(tree->data->cmd->args[i++])
			// 	free(tree->data->cmd->args[i]);
			free(tree->data->cmd->args);
			tree->data->cmd->args = NULL;
		}
		free(tree->data->cmd);
	}
	else if (tree->type == REDIR)
	{
		if (tree->data->red)
			free_redir(tree->data->red);
		tree->data->red = NULL;
	}
	else if (tree->type == PIPE)
	{
		if (tree->data->pipe->value)
			free(tree->data->pipe->value);
		if (tree->data->pipe)
			free(tree->data->pipe);
	}
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree->data);
	free(tree);
}

void     helper(t_token **token, char **env)
{
	t_node *tree = NULL;
	// t_token *tmp;
	char **str;

	str = env;
	// tmp = *token;
	if (*token == NULL)
		return ;
	heredoc(*token, str); 
	if (parss_command(*token) == 1)
	{
		expand(token, str);
		concatenation_token(*token);
		take_args(*token);
		tree = pipeline(token);
		g_v->g_exit_code = ft_execution(tree, str, 1);
		// free_tree(tree);
		// print_tree(tree);
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

t_node *new_redir(t_token *token)
{
	t_node	*node;

	node = ft_calloc1(1 ,sizeof(t_node));
	ft_lstadd_back_free(&g_v->adress, init_free(node));
	node->data = ft_calloc1(1 ,sizeof(t_data));
	ft_lstadd_back_free(&g_v->adress, init_free(node->data));
	node->data->red = ft_calloc1(1, sizeof(t_redir));
	ft_lstadd_back_free(&g_v->adress, init_free(node->data->red));
	node->data->red->value = ft_strdup1(token->value);
	node->data->red->type = token->type;
	node->type = REDIR;
	return (node);
}

t_node *new_node(t_token *token)
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

t_node *command(t_token **token)
{
	t_token *tmp;
	t_token *tmp2;
	t_node *node;
	
	tmp = (*token);
	if((*token) && ((*token)->type == TOKEN_ID || (*token)->type == TOKEN_STRING))
	{
		tmp2 = (*token);
		*token = (*token)->next;
		node = new_node(tmp2);
		// free (tmp2);
		while ((*token) && ((*token)->type == TOKEN_ID || (*token)->type == TOKEN_STRING))
		{
			// tmp2 = (*token);
			*token = (*token)->next;
			// free (tmp2);
		}
		return(node);
	}
	return NULL;
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

t_node  *pipeline(t_token **token)
{
	// t_token *tmp;
	t_node *left;
	t_node *new;

	if (token == NULL)
		return NULL;
	left = rederiction(token);
	while((*token) && (*token)->type == TOKEN_PIPE)
	{
		new = new_pipe(*token);
		new->type = PIPE;
		// tmp = (*token);
		*token = (*token)->next;
		// free(tmp);
		new->left = left;
		new->right = pipeline(token);
		left = new;
	}
	return left;
}

t_redir *ft_lstlast_red(t_redir *lst)
{
	if (lst == NULL)
		return NULL;
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return lst;
}
void ft_last_back_red(t_redir **lst, t_redir *new)
{
	t_redir *tmp;

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

t_node	*rederiction(t_token **token)
{
	// t_token *tmp2;
	t_node *left;
	t_node *node;
	t_redir *tmp;
	t_token *tmp_token;
	
	left = command(token);
	if (left == NULL)
	{
		tmp_token = *token;
		while (tmp_token && (tmp_token->type == TOKEN_REDIR_IN ||\
		 tmp_token->type == TOKEN_REDIR_OUT ||\
		 tmp_token->type == TOKEN_REDIR_APPEND ||\
		 tmp_token->type == TOKEN_OUTFILE ||\
		 tmp_token->type == TOKEN_FILE))
		 {
			tmp_token = tmp_token->next;
		 }
		 if (tmp_token && (tmp_token->type == TOKEN_ID || tmp_token->type == TOKEN_STRING))
			left = new_node(tmp_token);
	}
	if ((*token) && ((*token)->type == TOKEN_REDIR_IN ||\
	 (*token)->type == TOKEN_REDIR_OUT ||\
	 (*token)->type == TOKEN_REDIR_APPEND))
	{
		node = new_redir(*token);
		tmp = node->data->red;
		// tmp2 = (*token);
		(*token) = (*token)->next;
		// free(tmp2);
		while ((*token) && ((*token)->type == TOKEN_REDIR_IN ||\
		 (*token)->type == TOKEN_REDIR_OUT ||\
		 (*token)->type == TOKEN_REDIR_APPEND ||\
		 (*token)->type == TOKEN_OUTFILE ||\
		 (*token)->type == TOKEN_FILE))
		 {
			tmp->next = create_redirection(*token);
			tmp = tmp->next;
			// tmp2 = (*token);
			(*token) = (*token)->next;
			// free(tmp2);
		 	if ((*token) && ((*token)->type == TOKEN_ID || (*token)->type == TOKEN_STRING))
			{
				// tmp2 = (*token);
				(*token) = (*token)->next;
				// free(tmp2);
			}
		 }
		 node->left = left;
		 left = node;
	}
	return left;
}
