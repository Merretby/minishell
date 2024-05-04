/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:43:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/04 09:52:54 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_check_alnum(char c)
{
	if (c == '$' || c == '|' || c == '>' || c == '<' || c == '&' || c == '"' || c == '\0' || c == ' ' || (c >= 9 && c <= 13))
		return (0);
	return (1);
}

char	*get_the_word(t_lexer *lexer)
{
	char	*str;
	int		j;
	t_lexer	tmp;

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
	while (ft_check_alnum(lexer->c))
	{
		str[j] = lexer->c;
		j++;
		if (!ft_isalnum(lexer->content[lexer->i + 1]))
			break ;
		advance(lexer);
	}
	str[j] = '\0';
	return (str);
}
