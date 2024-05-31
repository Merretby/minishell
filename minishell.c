/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/31 15:07:35 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
		printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay(); 
}

void	check_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
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
	//check_signal();
	str = readline("\033[1;32mminishell@1337~$ \033[0m");
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
		str = readline("\033[1;32mminishell@1337~$ \033[0m");
	}
	printf("exit\n");
}
