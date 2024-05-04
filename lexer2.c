/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:02:49 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/04 09:50:19 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[lexer->i];
	return (lexer);
}

static void	lexer_to_next_token2(t_lexer **lexer, t_token **token)
{
	if ((*lexer)->c == '<')
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_REDIR_IN,
					"<")));
	else if ((*lexer)->c == '>')
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_REDIR_OUT,
					">")));
	else if ((*lexer)->c == '&')
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_AMPERSAND,
					"&")));
	else if ((*lexer)->c == '$')
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_DOLLAR,
					"$")));
	else if ((*lexer)->c == '"')
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_STRING,
					get_the_string(*lexer))));
	else if ((*lexer)->c == '|')
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_PIPE,
					"|")));
	else
		ft_lstadd_back1(token, advance_token(*lexer, init_token(TOKEN_ID,
					get_the_word(*lexer))));
}

void	lexer_to_next_token(t_lexer *lexer, t_token **token)
{
	while (lexer->c != '\0' && ft_strlen(lexer->content) > lexer->i)
	{
		if (lexer->c == ' ' || (lexer->c >= 9 && lexer->c <= 13))
			skip_whitespace(lexer);
		else if (lexer->c == '>' && lexer->content[lexer->i + 1] == '>')
		{
			ft_lstadd_back1(token, advance_token(lexer,
					init_token(TOKEN_REDIR_APPEND, ">>")));
			advance(lexer);
		}
		else if (lexer->c == '<' && lexer->content[lexer->i + 1] == '<')
		{
			ft_lstadd_back1(token, advance_token(lexer,
					init_token(TOKEN_HEREDOC, "<<")));
			advance(lexer);
		}
		else
			lexer_to_next_token2(&lexer, token);
	}
}
