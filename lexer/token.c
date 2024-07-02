/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:38:13 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/02 10:47:53 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_token(int type, char *value, char c)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	ft_lstadd_back_free(&g_v->adress, init_free(token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	if (c == '"')
		token->flag = 1;
	else if (c == '\'')
		token->flag = 0;
	else
		token->flag = -1;
	token->helper_flag = 0;
	token->next = NULL;
	token->prev = NULL;
	token->args = NULL;
	token->arg = NULL;
	return (token);
}

t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	ft_lstadd_back_free(&g_v->adress, init_free(lexer));
	if (!lexer)
		return (NULL);
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[lexer->i];
	return (lexer);
}

int	ft_check_alnum(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '"' || c == '\0'
		|| c == ' ' || (c >= 9 && c <= 13) || c == '\'' || c == ';' || c == '&')
		return (0);
	return (1);
}
