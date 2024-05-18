/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:51:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/18 12:06:05 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_redir(t_redir*red);

void   print_tree(t_node *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type == PIPE)
	{
		printf("PIPE: %s\n", tree->data->red->value);
	}
	else if (tree->type == CMD)
	{
		printf("CMD: %s\n", tree->data->cmd->value);
		for (int i = 0; tree->data->cmd->args[i]; i++)
			printf("args: %s\n", tree->data->cmd->args[i]);
	}
	else if (tree->type == REDIR)
	{
		printf("REDIR: %s\n", tree->data->red->value);
		// print_redir(tree->data->red);
	}
	print_tree(tree->left);
	print_tree(tree->right);
}

void     helper(t_token *token)
{
	t_node *tree = NULL;

	if (token == NULL)
		return ;
	if (parss_command(token) == 1)
		tree = pipeline(&token);
	print_tree(tree);
}

t_redir	*create_redirection(t_token *token)
{
	t_redir	*red;

	red = malloc(sizeof(t_redir));
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
	node->data->cmd->args = NULL;
	node->type = CMD;
	return (node);
}

t_node *command(t_token **token)
{
	t_node *new;
	char *str;
	
	if((*token) && ((*token)->type == TOKEN_ID || (*token)->type == TOKEN_STRING\
		|| (*token)->type == TOKEN_DOLLAR))
	{
		new = new_node(*token);
		*token = (*token)->next;
		while ((*token) && ((*token)->type == TOKEN_ID || (*token)->type == TOKEN_STRING\
			|| (*token)->type == TOKEN_DOLLAR))
		{
			if ((*token)->prev->helper_flag == 1 || (*token)->prev->helper_flag == 0)
				new->data->cmd->value  = ft_strjoin(new->data->cmd->value, (*token)->value);
			else
			{
				str = ft_strjoin(new->data->cmd->value, " ");
				new->data->cmd->value = ft_strjoin(str, (*token)->value);
				free (str);
			}
			*token = (*token)->next;
		}
		if (new->data->cmd->value != NULL)
			new->data->cmd->args = ft_split(new->data->cmd->value, ' ');
		return new;
	}
	return NULL;
}


t_node  *pipeline(t_token **token)
{
	t_node *left;
	t_node *new;

	if (token == NULL)
		return NULL;
	left = rederiction(token);
	// printf("rani dezt mn pipe\n");
	while((*token) && (*token)->type == TOKEN_PIPE)
	{
		new = new_redir(*token);
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

void print_redir(t_redir*red)
{
	while (red)
	{
		printf("redirection--> %s\n", red->value);
		red = red->next;
	}
}

t_node	*rederiction(t_token **token)
{
	t_node *left;
	t_node *red;
	t_redir *tmp;

	
	left = command(token);
	if ((*token) && ((*token)->type == TOKEN_HEREDOC))
	{
		red = new_redir((*token));
		red->left = left;
		*token = (*token)->next;
		red->right = command(token);
		left = red;
	}
	if ((*token) && ((*token)->type == TOKEN_REDIR_IN ||\
	 (*token)->type == TOKEN_REDIR_OUT ||\
	 (*token)->type == TOKEN_REDIR_APPEND ||\
	 (*token)->type == TOKEN_OUTFILE ||\
	 (*token)->type == TOKEN_FILE))
	{
		red = new_redir(*token);
		tmp = red->data->red;
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
		 }
		 red->left = left;
		 red->right = pipeline(token);
		 left = red;
	}
	return left;
}
