/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:43:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/03 18:49:29 by moer-ret         ###   ########.fr       */
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
char	*get_the_string(t_lexer *lexer)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * ft_strlen(lexer->content));
	advance(lexer);
	while (lexer->c != '"' && lexer->c != '\0')
	{
		str[i] = lexer->c;
		i++;
		advance(lexer);
	}
	str[i] = '\0';
	return (str);
}

char	*get_the_word(t_lexer *lexer)
{
	char *str;
	int j;
	t_lexer tmp;

	tmp = *lexer;
	j = 0;
	while (ft_isalnum(tmp.c))
	{
		j++;
		tmp.i++;
		tmp.c = tmp.content[tmp.i];
	}
	str = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (ft_isalnum(lexer->c))
	{
		str[j] = lexer->c;
		j++;
		if (!ft_isalnum(lexer->content[lexer->i + 1]))
			break;
		advance(lexer);
	}
	str[j] = '\0';
	return (str);
}

static void lexer_to_next_token2(t_lexer **lexer, t_token **token)
{
		if ((*lexer)->c == '<')
			ft_lstadd_back1(token,advance_token(*lexer, init_token(TOKEN_REDIR_IN, "<")));
		else if ((*lexer)->c == '>')
			ft_lstadd_back1(token,advance_token(*lexer, init_token(TOKEN_REDIR_OUT, ">")));
		else if ((*lexer)->c == '&')
			ft_lstadd_back1(token,advance_token(*lexer, init_token(TOKEN_AMPERSAND, "&")));
		else if ((*lexer)->c == '$')
			ft_lstadd_back1(token,advance_token(*lexer, init_token(TOKEN_DOLLAR, "$")));
}

t_token	*lexer_to_next_token(t_lexer *lexer)
{
	t_token *token = NULL;
	while (lexer->c != '\0' && ft_strlen(lexer->content) > lexer->i)
	{
		if (lexer->c == ' ' || (lexer->c >= 9 && lexer->c <= 13))
			skip_whitespace(lexer);
		if (ft_isalnum(lexer->c))
			ft_lstadd_back1(&token,advance_token(lexer, init_token(TOKEN_ID, get_the_word(lexer))));
		else if (lexer->c == '"')
			ft_lstadd_back1(&token,advance_token(lexer, init_token(TOKEN_STRING, get_the_string(lexer))));
		else if (lexer->c == '|')
			ft_lstadd_back1(&token,advance_token(lexer, init_token(TOKEN_PIPE, "|")));
		else if (lexer->c == '>' && lexer->content[lexer->i + 1] == '>')
		{
			ft_lstadd_back1(&token,advance_token(lexer, init_token(TOKEN_REDIR_APPEND, ">>")));
			advance(lexer);
		}
		else if (lexer->c == '<' && lexer->content[lexer->i + 1] == '<')
		{
			ft_lstadd_back1(&token,advance_token(lexer, init_token(TOKEN_HEREDOC, "<<")));
			advance(lexer);
		}
		else
			lexer_to_next_token2(&lexer, &token);
	}
	return (token);
}
