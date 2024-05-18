/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/18 14:05:52 by monachit         ###   ########.fr       */
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
	(void)env;
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
		// 	printf("Token type:%s\n", defin(token->type));
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
