/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:43:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/21 18:02:30 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*defin(int c)
{
	switch (c)
	{
	case TOKEN_REDIR_OUT:
		return ("REDIR_OUT");
	case TOKEN_REDIR_IN:
		return ("REDIR_IN");
	case TOKEN_PIPE:
		return ("PIPE");
	case TOKEN_DOLLAR:
		return ("DOLLAR");
	case TOKEN_STRING:
		return ("STRING");
	case TOKEN_REDIR_APPEND:
		return ("APPEND");
	case TOKEN_HEREDOC:
		return ("HEREDOC");
	case TOKEN_OUTFILE:
		return ("OUTFILE");
	case TOKEN_FILE:
		return ("FILE");
	default:
		return ("CMD");
	}
	return (NULL);
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
	advance(lexer);
	j = 0;
	while (lexer->c != c && lexer->c != '\0')
	{
		str[j++] = lexer->c;
		advance(lexer);
		if (lexer->c == '\0')
		{
			printf("minishell: not close with `%c'\n", c);
			return (NULL);
		}
	}
	str[j] = '\0';
	return (str);
}

int	ft_check_alnum(char c)
{
	// 3la 9bal had lcase ls -al ... 5asa t3ti ls / -al
	if (c == '$' || c == '|' || c == '>' || c == '<' || c == '"' || c == '\0'
		|| c == ' ' || (c >= 9 && c <= 13) || c == '\'')
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
	while (ft_check_alnum(tmp.c))
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
		if (!ft_check_alnum(lexer->content[lexer->i + 1]))
			break ;
		advance(lexer);
	}
	str[j] = '\0';
	return (str);
}
