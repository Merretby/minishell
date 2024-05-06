/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/06 17:53:32 by moer-ret         ###   ########.fr       */
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
	(void)env;
	str = readline("minishell > ");
	while (str)
	{
		// if (ft_strncmp(str, "env", 3) == 0)	
		// 	take_env(env);
		lexer = init_lexer(str);
		lexer_to_next_token(lexer, &token);
		join_cmd(token);
		// while (token)
		// {
		// 	printf("type: %s  value: %s  helper_flag: %d\n", defin(token->type), token->value, token->helper_flag);
		// 	token = token->next;
		// }
		ft_free(&token, &lexer);
		add_history(str);
		free(str);
		str = readline("minishell > ");
	}
}
