/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:43:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/07/02 10:47:47 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*get_the_string(t_lexer *lexer, char c)
{
	t_lexer	tmp;
	char	*str;
	size_t	j;

	tmp = *lexer;
	j = 0;
	tmp.c = tmp.content[++tmp.i];
	while (tmp.c != c && tmp.c != '\0')
	{
		j++;
		tmp.c = tmp.content[tmp.i++];
	}
	str = malloc(sizeof(char) * (j + 1));
	ft_lstadd_back_free(&g_v->adress, init_free(str));
	advance(lexer);
	j = 0;
	while (lexer->c != c && lexer->c != '\0')
	{
		str[j++] = lexer->c;
		advance(lexer);
	}
	str[j] = '\0';
	return (str);
}

char	*get_the_word(t_lexer *lexer)
{
	char	*str;
	int		j;
	t_lexer	tmp;

	tmp = *lexer;
	j = 0;
	while (ft_check_alnum(tmp.c))
	{
		j++;
		tmp.i++;
		tmp.c = tmp.content[tmp.i];
	}
	str = malloc(sizeof(char) * (j + 1));
	ft_lstadd_back_free(&g_v->adress, init_free(str));
	j = 0;
	while (ft_check_alnum(lexer->c))
	{
		str[j] = lexer->c;
		j++;
		if (!ft_check_alnum(lexer->content[lexer->i + 1]))
			break ;
		advance(lexer);
	}
	str[j] = '\0';
	return (str);
}
