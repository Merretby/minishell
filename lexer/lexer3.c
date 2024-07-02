/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:46:08 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/02 10:47:05 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_append_nor2(t_lexer **lexer, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if ((*lexer)->c == ft_isalnum((*lexer)->c))
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

void	redirection_append(t_lexer **lexer, t_token **token)
{
	ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_REDIR_APPEND,
				">>", (*lexer)->c)));
	advance(*lexer);
	if ((*lexer)->c == ' ' || ((*lexer)->c >= 9 && (*lexer)->c <= 13))
		skip_whitespace(*lexer);
	if ((*lexer)->c != '\0')
		lexer_append_nor2(lexer, token);
}

void	lexer_redirection_nor2(t_lexer **lexer, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if ((*lexer)->c == ft_isalnum((*lexer)->c) || (*lexer)->c == '/')
	{
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_FILE,
					get_the_word(*lexer), (*lexer)->c)));
		if ((*lexer)->c == '\'' || (*lexer)->c == '"')
		{
			tmp = ft_lstlast1(*token);
			tmp->helper_flag = 1;
		}
	}
	else if ((*lexer)->c == '\'' || (*lexer)->c == '"')
	{
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_FILE,
					get_the_string(*lexer, (*lexer)->c), (*lexer)->c)));
		if ((*lexer)->c == '\'' || (*lexer)->c == '"')
		{
			tmp = ft_lstlast1(*token);
			tmp->helper_flag = 1;
		}
	}
}

void	redirection2(t_lexer **lexer, t_token **token)
{
	ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_REDIR_IN, "<",
				(*lexer)->c)));
	if ((*lexer)->c == ' ' || ((*lexer)->c >= 9 && (*lexer)->c <= 13))
		skip_whitespace(*lexer);
	if ((*lexer)->c != '\0')
		lexer_redirection_nor2(lexer, token);
}

void	string(t_lexer **lexer, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if ((*lexer)->c == '\'')
	{
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_STRING,
					get_the_string(*lexer, '\''), (*lexer)->c)));
	}
	else if ((*lexer)->c == '"')
	{
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_STRING,
					get_the_string(*lexer, '"'), (*lexer)->c)));
	}
	if (ft_isalnum((*lexer)->content[(*lexer)->i]) || (*lexer)->c == '$')
	{
		tmp = ft_lstlast1(*token);
		tmp->helper_flag = 1;
	}
	else if ((*lexer)->c == '\'' || (*lexer)->c == '"')
	{
		tmp = ft_lstlast1(*token);
		tmp->helper_flag = 1;
	}
}
