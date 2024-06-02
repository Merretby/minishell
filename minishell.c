/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/06/02 18:10:50 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_syntax(char *str)
{
	char c;
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			break;
		}
		i++;
	}
	while (str[i])
	{
		i++;
		if (str[i] == c)
			return (1);
		if (str[i] == '\0')
		{
			printf("minishell: syntax error '%c'\n", c);
			return (0);
		}
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_lexer	*lexer;
	t_token	*token;

	(void)ac;
	(void)av;
	lexer = NULL;
	token = NULL;
	str = readline("minishell> ");
	while (str)
	{
		if (check_syntax(str))
		{
			lexer = init_lexer(str);
			lexer_to_next_token(lexer, &token);
			helper(&token, env);
			ft_free(&token, &lexer);
		}
		add_history(str);
		free(str);
		str = readline("minishell> ");
	}
}
