/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/06/28 16:57:12 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_g_var	*g_v;

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

void	main2(t_token **token, t_lexer **lexer, char **env)
{
	helper(token, env);
	free(*lexer);
	ft_free(token, lexer);
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
	g_v = (t_g_var *)malloc(sizeof(t_g_var));
	g_v->g_exit_code = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	str = readline("\033[0;32mminishell~$42 \033[0m");
	while (str)
	{
		if (check_syntax(str))
		{
			lexer = init_lexer(str);
			lexer_to_next_token(&lexer, &token);
			main2(&token, &lexer, env);
		}
		if (str[0] != '\0')
			add_history(str);
		free(str);
		str = readline("\033[0;32mminishell~$42 \033[0m");
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
	}
}