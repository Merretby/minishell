/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 08:37:18 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/31 22:55:25 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parss_command(t_token *token)
{
	t_token	*tmp;

	tmp = token;

	if (tmp && tmp->type == TOKEN_PIPE)
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (0);
	}
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE && tmp->next == NULL)
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			return (0);
		}
		if (tmp->type == TOKEN_PIPE && tmp->next->type == TOKEN_PIPE)
		{
			printf("minishell: syntax error near unexpected token '||'\n");
			return (0);
		}
		if ((tmp->type == TOKEN_REDIR_IN || tmp->type == TOKEN_REDIR_OUT ||\
		 	tmp->type == TOKEN_HEREDOC || tmp->type == TOKEN_REDIR_APPEND) && tmp->next == NULL)
		{
			printf("minishell: syntax error near unexpected token 'newline'\n");
			return (0);
		}
		if ((tmp->type == TOKEN_REDIR_APPEND && tmp->next->type == TOKEN_REDIR_OUT) \
			|| (tmp->type == TOKEN_REDIR_IN && tmp->next->type == TOKEN_REDIR_OUT))
		{
			printf("minishell: syntax error near unexpected token `>'\n");
			return (0);
		}
		if (tmp->type == TOKEN_REDIR_OUT && tmp->next->type == TOKEN_REDIR_IN)
		{
			printf("minishell: syntax error near unexpected token `<'\n");
			return (0);
		}
		if (tmp->next && (tmp->type == TOKEN_REDIR_IN \
			|| tmp->type == TOKEN_REDIR_OUT ||tmp->type == TOKEN_HEREDOC \
			|| tmp->type == TOKEN_REDIR_APPEND)\
			&& tmp->next->type == TOKEN_PIPE)
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			return (0);
		}
		if (tmp->type == TOKEN_ERROR)
		{
			printf("minishell: syntax error near unexpected token \n");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
