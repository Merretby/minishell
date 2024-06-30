/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/06/30 15:02:53 by moer-ret         ###   ########.fr       */
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

void	*ft_calloc1(size_t nmemb, size_t size)
{
	void	*str;
	size_t	i;

	i = -1;
	if (size != 0 && nmemb > (i / size))
		return (NULL);
	str = malloc(nmemb * size);
	// ft_lstadd_back_free(&g_v->adress, init_free(str));
	if (!str)
		return (NULL);
	ft_bzero(str, (size * nmemb));
	return (str);
}
char	*ft_strdup1(const char *src)
{
	size_t		i;
	size_t		size;
	char		*ls;

	i = 0;
	size = 0;
	while (src[size] != '\0')
		size++;
	ls = malloc((size + 1) * sizeof(char));
	ft_lstadd_back_free(&g_v->adress, init_free(ls));
	if (!ls)
		return (NULL);
	while (src[i] != '\0')
	{
		ls[i] = (char )src[i];
		i++;
	}
	ls[i] = '\0';
	return (ls);
}

void signal_norme(void)
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
	g_v = (t_g_var *)malloc(sizeof(t_g_var));
	g_v->adress = NULL;
	g_v->g_exit_code = 0;
	signal_norme();
	str = readline("\033[0;32mminishell~$42 \033[0m");
	while (str)
	{
		lexer = NULL;
		token = NULL;
		*retur_nvalue() = -1;
		if (check_syntax(str))
			main2(&token, &lexer, env, str);
		if (str[0] != '\0')
			add_history(str);
		free(str);
		str = readline("\033[0;32mminishell~$42 \033[0m");
		signal_norme();
	}
	ft_lstclear_free(&g_v->adress);
}
