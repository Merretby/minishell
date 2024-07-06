/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/04 21:32:08 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_g_var	*g_v;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", STDIN_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_v->g_exit_code = 130;
}

int	check_syntax(char *str)
{
	char	c;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			break ;
		}
		i++;
	}
	while (str[i])
	{
		if (str[++i] == c)
			return (1);
		if (str[i] == '\0')
		{
			ft_putstr_fd("minishell: syntax error \n", 2);
			g_v->g_exit_code = 2;
			return (0);
		}
	}
	return (1);
}

void	main2(t_token **token, t_lexer **lexer, char **env, char *str)
{
	*lexer = init_lexer(str);
	lexer_to_next_token(lexer, token);
	helper(token, env);
}

void	signal_norme(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_lexer	*lexer;
	t_token	*token;

	(void)ac;
	(void)av;
	init_global();
	signal_norme();
	str = readline("\033[0;32mminishell~$42 \033[0m");
	ft_lstadd_back_free(&g_v->adress, init_free(str));
	while (str)
	{
		lexer = NULL;
		token = NULL;
		*retur_nvalue() = -1;
		if (check_syntax(str))
			main2(&token, &lexer, env, str);
		if (str[0] != '\0')
			add_history(str);
		str = readline("\033[0;32mminishell~$42 \033[0m");
		ft_lstadd_back_free(&g_v->adress, init_free(str));
	}
	ft_lstclear_free(&g_v->adress);
	printf("exit\n");
}
