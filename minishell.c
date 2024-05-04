/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/04 11:00:18 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;
	t_lexer	*words;
	t_token	*token;

	words = NULL;
	token = NULL;
	str = readline("minishell > ");
	while (str)
	{
		words = init_lexer(str);
		lexer_to_next_token(words, &token);
		while (token)
		{
			printf("type: %d, value: %s\n", token->type, token->value);
			token = token->next;
		}
		add_history(str);
		str = readline("minishell > ");
	}
}
