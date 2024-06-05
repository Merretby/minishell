/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/06/05 13:12:49 by mnachit          ###   ########.fr       */
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
	str = readline("\033[0;32mminishell~$42 \033[0m");
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
		str = readline("\033[0;32mminishell~$42 \033[0m");
	}
	return (0);1
	
}
