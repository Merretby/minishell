/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:52:04 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/02 10:46:59 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_redirection_nor(t_lexer **lexer, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if ((*lexer)->c == ft_isalnum((*lexer)->c) || (*lexer)->c == '/')
	{
		ft_lstadd_back1(token, advance_token(*lexer,
				init_token(TOKEN_OUTFILE, get_the_word(*lexer),
					(*lexer)->c)));
		if ((*lexer)->c == '\'' || (*lexer)->c == '"')
		{
			tmp = ft_lstlast1(*token);
			tmp->helper_flag = 1;
		}
	}
	else if ((*lexer)->c == '\'' || (*lexer)->c == '"')
	{
		ft_lstadd_back1(token, advance_token(*lexer,
				init_token(TOKEN_OUTFILE, get_the_string(*lexer,
						(*lexer)->c), (*lexer)->c)));
		if ((*lexer)->c == '\'' || (*lexer)->c == '"')
		{
			tmp = ft_lstlast1(*token);
			tmp->helper_flag = 1;
		}
	}
}

void	redirection(t_lexer **lexer, t_token **token)
{
	if ((*lexer)->c == '>')
	{
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_REDIR_OUT,
					">", (*lexer)->c)));
		if ((*lexer)->c == ' ' || ((*lexer)->c >= 9 && (*lexer)->c <= 13))
			skip_whitespace(*lexer);
		if ((*lexer)->c != '\0')
			lexer_redirection_nor(lexer, token);
	}
	else if ((*lexer)->c == '<')
		redirection2(lexer, token);
}

void	lexer_to_next_token2(t_lexer **lexer, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if ((*lexer)->c == '&' || (*lexer)->c == ';' || (*lexer)->c == '('
		|| (*lexer)->c == ')')
	{
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_ERROR,
					(*lexer)->content, (*lexer)->c)));
	}
	if (((*lexer)->c == '"') || ((*lexer)->c == '\''))
		string(lexer, token);
	else if ((*lexer)->c == '|')
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_PIPE, "|",
					(*lexer)->c)));
	else
	{
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_ID,
					get_the_word(*lexer), (*lexer)->c)));
		if ((*lexer)->c == '\'' || (*lexer)->c == '"')
		{
			tmp = ft_lstlast1(*token);
			tmp->helper_flag = 1;
		}
	}
}

void	lexer_heredoc(t_lexer **lexer, t_token **token)
{
	t_token	*tmp;

	ft_lstadd_back1(token, advance_token((*lexer),
			init_token(TOKEN_HEREDOC, "<<", (*lexer)->c)));
	advance((*lexer));
	if ((*lexer)->c == ' ' || ((*lexer)->c >= 9 && (*lexer)->c <= 13))
		skip_whitespace((*lexer));
	if ((*lexer)->c == ft_isalnum((*lexer)->c) || (*lexer)->c == '/')
	{
		ft_lstadd_back1(token, advance_token((*lexer),
				init_token(TOKEN_EOF, get_the_word((*lexer)),
					(*lexer)->c)));
		if ((*lexer)->c == '\'' || (*lexer)->c == '"')
		{
			tmp = ft_lstlast1(*token);
			tmp->helper_flag = 1;
		}
	}
}

void	lexer_to_next_token(t_lexer **lexer, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while ((*lexer)->c != '\0' && ft_strlen((*lexer)->content) > (*lexer)->i)
	{
		if ((*lexer)->c == ' ' || ((*lexer)->c >= 9 && (*lexer)->c <= 13))
			skip_whitespace((*lexer));
		else if ((*lexer)->c == '>' && (*lexer)->content[(*lexer)->i
				+ 1] == '>')
			redirection_append(lexer, token);
		else if ((*lexer)->c == '<' && (*lexer)->content[(*lexer)->i
				+ 1] == '<')
			lexer_heredoc(lexer, token);
		else if ((*lexer)->c == '<')
			redirection(lexer, token);
		else if ((*lexer)->c == '>')
			redirection(lexer, token);
		else
			lexer_to_next_token2(lexer, token);
	}
}
