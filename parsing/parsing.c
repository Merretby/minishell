/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:51:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/30 15:39:37 by moer-ret         ###   ########.fr       */
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
		printf("PIPE: %s\n", tree->data->pipe->value);
	}
	else if (tree->type == CMD)
	{
		// if (tree->data->cmd->value != NULL)
		printf("CMD: %s\n", tree->data->cmd->value);
		if (tree->data->cmd->args != NULL)
		{
			for (int i = 0; tree->data->cmd->args[i]; i++)
				printf("args[%d]: %s\n", i, tree->data->cmd->args[i]);
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

void	del_preve_token(t_token **token)
{
	t_token *tmp;

	if (token == NULL)
		return ;
	tmp = *token;
	*token = (*token)->next;
	free(tmp->value);
	free(tmp);
}

void	concatenation_token(t_token *token)
{
	t_token *tmp;
	t_token *next;
	char *concatenated;
	
	tmp = token;
	if (token == NULL)
		return ;
	while (token)
	{
		if (token->helper_flag == 1)
		{
			next = token->next;
			while (next && (next->type == TOKEN_ID || next->type == TOKEN_STRING || next->type == TOKEN_DOLLAR))
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
	while (tmp)
	{
		printf("value: %s\n", tmp->value);
		tmp = tmp->next;
	}
}

void     helper(t_token *token, char **env)
{
	// t_node *tree = NULL;
	char **str;

	if (token == NULL)
		return ;
	if (parss_command(token) == 1)
	{
		str = env;
		heredoc(token, str);
		expand(token, str);
		concatenation_token(token);
		// tree = pipeline(&token);
		// ft_execution(tree, str, 1);
		// print_tree(tree);
	}
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

t_node	*init_pipe(t_token *token)
{
	t_node *node;

	node = ft_calloc(1, sizeof(t_node));
	node->data = ft_calloc(1, sizeof(t_data));
	node->data->pipe = ft_calloc(1, sizeof(t_pipe));
	node->data->pipe->value = ft_strdup(token->value);
	node->data->pipe->type = token->type;
	node->type = PIPE;
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

// void myfree(void * p) 
// {
//     size_t	*in;
	
// 	in = p;
//     if (in) 
// 	{
//         --in; 
// 		free(in);
//     }
// }

// void *mymalloc(size_t n) 
// {
//     size_t *result;
	 
// 	result = malloc(n + sizeof(size_t));
//     if (result) 
// 	{
// 		*result = n;
// 		++result;
// 		ft_memset(result,0,n);
// 	}
//     return result;
// }

// size_t getsize(void * p) 
// {
//     size_t * in = p;
//     if (in) 
// 	{
// 		--in;
// 		return *in;
// 	}
//     return -1;
// }


// void *reallocation(void *ptr,size_t size) 
// {
//     void *newptr;
//     int msize;
//     msize = getsize(ptr);
//     printf("msize=%d\n", msize);
//     if (size <= msize)
//         return ptr;
//     newptr = mymalloc(size);
//     ft_memcpy(newptr, ptr, msize);
//     myfree(ptr);
//     return newptr;
// }

// t_node *command(t_token **token)
// {
// 	t_node *new;
// 	char *str;
	
// 	if((*token) && ((*token)->type == TOKEN_ID || (*token)->type == TOKEN_STRING\
// 		|| (*token)->type == TOKEN_DOLLAR))
// 	{
// 		new = new_node(*token);
// 		*token = (*token)->next;
// 		while ((*token) && ((*token)->type == TOKEN_ID || (*token)->type == TOKEN_STRING\
// 			|| (*token)->type == TOKEN_DOLLAR))
// 		{
// 			if ((*token)->prev->helper_flag == 1)
// 				new->data->cmd->value  = ft_strjoin(new->data->cmd->value, (*token)->value);
// 			else
// 			{
// 				str = ft_strjoin(new->data->cmd->value, " ");
// 				new->data->cmd->value = ft_strjoin(str, (*token)->value);
// 				free (str);
// 			}
// 			*token = (*token)->next;
// 		}
// 		if (new->data->cmd->value != NULL)
// 			new->data->cmd->args = ft_split(new->data->cmd->value, ' ');
// 		return new;
// 	}
// 	return NULL;
// }

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
			if ((*token)->prev->helper_flag == 1)
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
	while((*token) && (*token)->type == TOKEN_PIPE)
	{
		new = init_pipe(*token);
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
	t_node *data;
	t_redir *tmp;

	
	left = command(token);
	// if ((*token) && ((*token)->type == TOKEN_HEREDOC))
	// {
	// 	data = new_redir((*token));
	// 	data->left = left;
	// 	*token = (*token)->next;
	// 	data->right = command(token);
	// 	left = data;
	// }
	if ((*token) && ((*token)->type == TOKEN_REDIR_IN ||\
	 (*token)->type == TOKEN_REDIR_OUT ||\
	 (*token)->type == TOKEN_REDIR_APPEND ||\
	 (*token)->type == TOKEN_OUTFILE ||\
	 (*token)->type == TOKEN_FILE || (*token)->type == TOKEN_EOF))
	{
		data = new_redir(*token);
		tmp = data->data->red;
		(*token) = (*token)->next;
		while ((*token) && ((*token)->type == TOKEN_REDIR_IN ||\
		 (*token)->type == TOKEN_REDIR_OUT ||\
		 (*token)->type == TOKEN_REDIR_APPEND ||\
		 (*token)->type == TOKEN_OUTFILE ||\
		 (*token)->type == TOKEN_FILE || (*token)->type == TOKEN_EOF))
		 {
			tmp->next = create_redirection(*token);
			tmp = tmp->next;
			(*token) = (*token)->next;
		 }
		 data->left = left;
		 left = data;
	}
	return left;
}
