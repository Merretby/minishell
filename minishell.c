/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/20 17:28:10 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_lexer	*lexer;
	t_token	*token;

	(void)ac;
	(void)av;
	lexer = NULL;
	token = NULL;
	str = readline("minishell > ");
	while (str)
	{
		// if (ft_strncmp(str, "env", 3) == 0)
		// 	take_env(env);
		lexer = init_lexer(str);
		lexer_to_next_token(lexer, &token);
		helper(token, env);
		// while (token)
		// {
		// 	printf("Token type:%s token: %s, flag: %d\n", defin(token->type), token->value, token->helper_flag);
		// 	token = token->next;
		// }
		// t_tree *tmp = create_tree(token);
		// while (tmp)
		// {
		// 	printf("cmd: %s\n", tmp->cmd);
		// 	tmp = tmp->right;
		// }
		ft_free(&token, &lexer);
		add_history(str);
		free(str);
		str = readline("minishell > ");
	}
}
