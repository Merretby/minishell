/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/03 17:46:13 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char    *str;
	t_lexer  *words = NULL;
	t_token  *token = NULL;
	str = readline("minishell > ");
	while (str)
	{
		words = init_lexer(str);
		token = lexer_to_next_token(words);
		while (token)
		{
			printf("type: %d, value: %s\n", token->type, token->value);
			token = token->next;
		}
		add_history(str);
		
		str = readline("minishell > ");
	}
}
