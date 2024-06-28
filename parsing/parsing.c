/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:51:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/06/28 15:04:58 by mnachit          ###   ########.fr       */
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
				concatenated = ft_strjoin(token->value, next->value);
				free(token->value);
				token->value = concatenated;
				token->helper_flag = token->next->helper_flag;
				token->next = next->next;
				free(next->value);
				free(next);
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
	new = ft_calloc(1, sizeof(t_args));
	new->args = ft_strdup(str);
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
		free(node->value);
		free(node);
		node = NULL;
	}
	else
	{
	
		node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		free(node->value);
		free(node);
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
				// delete_node(head,tmp2);
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
	token->arg = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	tmp = token->args;
	while (tmp)
	{
		token->arg[i] = ft_strdup(tmp->args);
		tmp = tmp->next;
		i++;
	}
	token->arg[i] = NULL;
}

void     helper(t_token **token, char **env)
{
	t_node *tree = NULL;
	char **str;

	if (*token == NULL)
		return ;
	if (parss_command(*token) == 1)
	{
		str = env;
		if (heredoc(*token, str) == 1)
			retu
		expand(token, str);
		concatenation_token(*token);
		take_args(*token);
		tree = pipeline(token);
		ft_execution(tree, str, 1);
		// print_tree(tree);
	}
	else
		g_exit_code = 2;
}

t_redir	*create_redirection(t_token *token)
{
	t_redir	*red;

	red = ft_calloc(1, sizeof(t_redir));
	red->value = ft_strdup(token->value);
	red->type = token->type;
	return (red);
}

t_node *new_redir(t_token *token)
{
	t_node	*node;

	node = ft_calloc(1 ,sizeof(t_node));
	node->data = ft_calloc(1 ,sizeof(t_data));
	node->data->red = ft_calloc(1, sizeof(t_redir));
	node->data->red->value = ft_strdup(token->value);
	node->data->red->type = token->type;
	node->type = REDIR;
	return (node);
}

t_node *new_node(t_token *token)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->data = ft_calloc(1, sizeof(t_data));
	node->data->cmd = ft_calloc(1, sizeof(t_cmd));
	if (token->value)
		node->data->cmd->value = ft_strdup(token->value);
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
	
	tmp = (*token);
	if((*token) && ((*token)->type == TOKEN_ID || (*token)->type == TOKEN_STRING))
	{
		*token = (*token)->next;
		while ((*token) && ((*token)->type == TOKEN_ID || (*token)->type == TOKEN_STRING))
			*token = (*token)->next;
		return(new_node(tmp));
	}
	return NULL;
}

t_node	*new_pipe(t_token *token)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->data = ft_calloc(1, sizeof(t_data));
	node->data->pipe = ft_calloc(1, sizeof(t_pipe));
	node->data->pipe->value = ft_strdup(token->value);
	node->data->pipe->type = token->type;
	node->type = PIPE;
	return (node);
}

t_node  *pipeline(t_token **token)
{
	t_node *left;
	t_node *new;

	if (token == NULL)
		return NULL;
	left = rederiction(token);
	while((*token) && (*token)->type == TOKEN_PIPE)
	{
		new = new_pipe(*token);
		new->type = PIPE;
		*token = (*token)->next;
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
		 {
			left = new_node(tmp_token);
			// left->data->cmd->value = ft_strdup(tmp_token->value);
			// left->data->cmd->args = ft_split(left->data->cmd->value, ' ');
		 }
	}
	if ((*token) && ((*token)->type == TOKEN_REDIR_IN ||\
	 (*token)->type == TOKEN_REDIR_OUT ||\
	 (*token)->type == TOKEN_REDIR_APPEND))
	{
		node = new_redir(*token);
		tmp = node->data->red;
		(*token) = (*token)->next;
		while ((*token) && ((*token)->type == TOKEN_REDIR_IN ||\
		 (*token)->type == TOKEN_REDIR_OUT ||\
		 (*token)->type == TOKEN_REDIR_APPEND ||\
		 (*token)->type == TOKEN_OUTFILE ||\
		 (*token)->type == TOKEN_FILE))
		 {
			tmp->next = create_redirection(*token);
			tmp = tmp->next;
			(*token) = (*token)->next;
		 	if ((*token) && ((*token)->type == TOKEN_ID || (*token)->type == TOKEN_STRING))
				(*token) = (*token)->next;
		 }
		 node->left = left;
		 left = node;
	}
	return left;
}