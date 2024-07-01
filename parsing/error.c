/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 08:37:18 by moer-ret          #+#    #+#             */
/*   Updated: 2024/06/28 23:46:03 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parss_command(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	signal(SIGINT, signal_handler);
	if (tmp && tmp->type == TOKEN_PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token '|'", 2);
		return (0);
	}
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE && tmp->next == NULL)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token '|'",
				2);
			return (0);
		}
		if (tmp->type == TOKEN_PIPE && tmp->next->type == TOKEN_PIPE)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token '||'",
				2);
			return (0);
		}
		if ((tmp->type == TOKEN_REDIR_IN || tmp->type == TOKEN_REDIR_OUT
				|| tmp->type == TOKEN_HEREDOC
				|| tmp->type == TOKEN_REDIR_APPEND) && tmp->next == NULL)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token 'newline'",
				2);
			return (0);
		}
		if ((tmp->type == TOKEN_REDIR_APPEND
				&& tmp->next->type == TOKEN_REDIR_OUT)
			|| (tmp->type == TOKEN_REDIR_IN
				&& tmp->next->type == TOKEN_REDIR_OUT)
			|| (tmp->type == TOKEN_REDIR_OUT
				&& tmp->next->type == TOKEN_REDIR_OUT))
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `>'",
				2);
			return (0);
		}
		if ((tmp->type == TOKEN_REDIR_OUT && tmp->next->type == TOKEN_REDIR_IN)
			|| (tmp->type == TOKEN_REDIR_IN
				&& tmp->next->type == TOKEN_REDIR_IN))
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `<'",
				2);
			return (0);
		}
		if (tmp->type == TOKEN_HEREDOC && tmp->next->type == TOKEN_HEREDOC)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `<<'",
				2);
			return (0);
		}
		if (tmp->type == TOKEN_REDIR_APPEND
			&& tmp->next->type == TOKEN_REDIR_APPEND)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `>>'",
				2);
			return (0);
		}
		if (tmp->next && (tmp->type == TOKEN_REDIR_IN
				|| tmp->type == TOKEN_REDIR_OUT || tmp->type == TOKEN_HEREDOC
				|| tmp->type == TOKEN_REDIR_APPEND)
			&& tmp->next->type == TOKEN_PIPE)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token '|'",
				2);
			return (0);
		}
		if (tmp->type == TOKEN_ERROR)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token", 2);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
