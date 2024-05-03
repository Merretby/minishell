/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:43:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/03 15:41:05 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer *init_lexer(char *content)
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[lexer->i];
	return (lexer);
}
void	advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && ft_strlen(lexer->content) > lexer->i)
	{
		lexer->i++;
		lexer->c = lexer->content[lexer->i];
	}
}

void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || (lexer->c >= 9 && lexer->c <= 13))
		advance(lexer);
}

t_token	*advance_token(t_lexer *lexer, t_token *token)
{
	advance(lexer);
	return (token);
}

t_token	*lexer_to_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && ft_strlen(lexer->content) > lexer->i)
	{
		if (lexer->c == ' ' || (lexer->c >= 9 && lexer->c <= 13))
			skip_whitespace(lexer);
		if (ft_isalnum(lexer->c))
			return (advance_token(lexer, init_token(TOKEN_ID, lexer->content)));
		else if (lexer->c == '"')
			return (advance_token(lexer, init_token(TOKEN_STRING, get_the_string(lexer))));
		else if (lexer->c == '|')
			return (advance_token(lexer, init_token(TOKEN_PIPE, "|")));
		else if (lexer->c == '<')
			return (advance_token(lexer, init_token(TOKEN_REDIR_IN, "<")));
		else if (lexer->c == '>')
			return (advance_token(lexer, init_token(TOKEN_REDIR_OUT, ">")));
	}
	return (NULL);
}
char	*get_the_string(t_lexer *lexer)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * ft_strlen(lexer->content));
	advance(lexer);
	while (lexer->i != '"' && lexer->i != '\0')
	{
		str[i] = lexer->i;
		i++;
		advance(lexer);
	}
	return (str);
}
