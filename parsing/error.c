/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 08:37:18 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/17 14:21:52 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parss_command(t_token *token)
{
	t_token	*tmp;
	t_token *tmp2;

	tmp = token;
	tmp2 = token;
	// while (tmp2)
	// {
	// 	printf("token: %s, value: %s\n", defin(tmp2->type), tmp2->value);
	// 	tmp2 = tmp2->next;
	// }
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
		if (token->next && (tmp->type == TOKEN_REDIR_IN \
			|| tmp->type == TOKEN_REDIR_OUT ||tmp->type == TOKEN_HEREDOC \
			|| tmp->type == TOKEN_REDIR_APPEND)\
			&& tmp->next->type == TOKEN_PIPE)
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
