/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/05 13:36:02 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*str;
	t_lexer	*lexer;
	t_token	*token;

	lexer = NULL;
	token = NULL;
	str = readline("minishell > ");
	while (str)
	{
		if (ft_strncmp(str, "env", 3) == 0)	
			take_env(env);
		lexer = init_lexer(str);
		lexer_to_next_token(lexer, &token);
		while (token)
		{
			printf("type--> %s,	value--> %s,	type_str--> %d\n", defin(token->type), token->value, token->flag);
			token = token->next;
		}
		add_history(str);
		str = readline("minishell > ");
	}
}
