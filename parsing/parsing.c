/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:51:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/16 08:32:09 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void   print_tree(t_node *tree)
{
	if(tree == NULL)
		return;
	printf("---> %s\n", tree->token->value);
	// if (tree->type == REDIR)
	// {
	// 	printf("redirection %s\n", tree->token->value);
	// }
	// else
	// {
	// 	printf("command %s\n", tree->token->value);
	// }
	print_tree(tree->left);
	print_tree(tree->right);
}

t_redir  *new_redir(t_token *token)
{
	t_redir *new;
	new = malloc(sizeof(t_redir));
	new->value = token->value;
	new->type = token->type;
	new->next = NULL;
	return new;
}

void     helper(t_token *token)
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
	char *str;
	
	if((*token) && ((*token)->type == TOKEN_ID || (*token)->type == TOKEN_STRING\
		|| (*token)->type == TOKEN_DOLLAR))
	{
		new = new_node(*token);
		new->type = CMD;
		*token = (*token)->next;
		while ((*token) && ((*token)->type == TOKEN_ID || (*token)->type == TOKEN_STRING\
			|| (*token)->type == TOKEN_DOLLAR))
		{
			if ((*token)->prev->helper_flag == 1 || (*token)->prev->helper_flag == 0)
				new->token->value = ft_strjoin(new->token->value, (*token)->value);
			else
			{
				str = ft_strjoin(new->token->value, " ");
				new->token->value = ft_strjoin(str, (*token)->value);
				free (str);
			}
			*token = (*token)->next;
		}
		return new;
	}
	else
	{
		if (*token)
		*token = (*token)->next;
		return (NULL);
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
	printf("rani dezt mn pipe\n");
	while((*token) && (*token)->type == TOKEN_PIPE)
	{
		new = new_node(*token);
		new->type = CMD;
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
	while (lst && lst->next)
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

void print_redir(t_redir *red)
{
	while (red)
	{
		printf("redirection %s\n", red->value);
		red = red->next;
	}
}

t_node	*rederiction(t_token **token)
{
	t_node *left;
	t_node *new;
	t_redir *red;
	t_redir *tmp;
	
	if (token == NULL)
		return NULL;
	new = NULL;
	left = command(token);
	if ((*token) && ((*token)->type == TOKEN_REDIR_IN ||\
	 (*token)->type == TOKEN_REDIR_OUT ||\
	 (*token)->type == TOKEN_REDIR_APPEND ||\
	 (*token)->type == TOKEN_OUTFILE ||\
	(*token)->type == TOKEN_FILE))
	{
		red = new_redir(*token);
		tmp = red;
		(*token) = (*token)->next;
		while ((*token) && ((*token)->type == TOKEN_REDIR_IN ||\
		 (*token)->type == TOKEN_REDIR_OUT ||\
		 (*token)->type == TOKEN_REDIR_APPEND ||\
		 (*token)->type == TOKEN_OUTFILE ||\
		 (*token)->type == TOKEN_FILE))
		 {
			printf("tokeb type %d	token value %s\n", (*token)->type, (*token)->value);
			ft_last_back_red(&red, new_redir(*token));
			(*token) = (*token)->next;
		 }
		 print_redir(tmp);
		 if (*token)
		 {
			printf ("token value fred %s\n", (*token)->value);
			if ((*token)->type == TOKEN_PIPE)
			{
				new = new_node((*token));
				(*token) = (*token)->next;
				new->left = left;
				new->right = pipeline(token);
				left = new;
			}
			else
			{
				printf("dezt hna\n");
				new = new_node((*token));
				new->type = REDIR;
				(*token) = (*token)->next;
				new->left = left;
				new->right = rederiction(token);
				left = new;
			}
		 }
	}
	return left;
}
