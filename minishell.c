/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/06/07 18:05:30 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
		printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
	g_exit_code = 130;
	return ;
}


void	check_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

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
	(void)env;
	lexer = NULL;
	token = NULL;
	check_signal();
	str = readline("\033[0;32mminishell~$42 \033[0m");
	while (str)
	{
		g_exit_code = 0;
		if (check_syntax(str))
		{
			lexer = init_lexer(str);
			lexer_to_next_token(&lexer, &token);
			// while (token)
			// {
			// 	printf("type : %s value : %s\n", defin(token->type), token->value);
			// 	token = token->next;
			// }
			helper(&token, env);
			free(lexer);
			ft_free(&token, &lexer);
		}
		add_history(str);
		free(str);
		str = readline("\033[0;32mminishell~$42 \033[0m");
	}
	return (0);
}
