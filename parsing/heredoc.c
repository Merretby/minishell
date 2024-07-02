/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:44:32 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/02 08:59:45 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	concatenation_norme(t_token **tmp, t_token **next)
{
	char	*str;

	str = ft_strjoin2((*tmp)->value, (*next)->value);
	(*tmp)->value = str;
	(*tmp)->helper_flag = (*tmp)->next->helper_flag;
	(*tmp)->next = (*tmp)->next->next;
	(*next) = (*tmp)->next;
}

char	*concatenation(t_token *token)
{
	t_token	*tmp;
	t_token	*next;

	tmp = token;
	g_v->g_flag = 1;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
		{
			tmp = tmp->next;
			if (tmp->helper_flag == 1)
			{
				next = tmp->next;
				while (next && (next->type == TOKEN_ID
						|| next->type == TOKEN_STRING))
				{
					concatenation_norme(&tmp, &next);
					if (tmp->helper_flag == 0)
						return (tmp->value);
				}
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup1(""));
	else if (ft_strlen(s + start) < len)
	{
		str = malloc(ft_strlen(s + start) + 1);
		ft_lstadd_back_free(&g_v->adress, init_free(str));
	}
	else
	{
		str = malloc(len + 1);
		ft_lstadd_back_free(&g_v->adress, init_free(str));
	}
	if (!str)
		return (NULL);
	while (s[start] && i < len)
	{
		str[i++] = s[start];
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	*expand_heredoc(char *line, char **env)
{
	int		i;
	int		j;
	char	*tmp;
	char	*before;
	char	*after;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			while (line[i] && line[i] != '$')
				i++;
			before = ft_substr2(line, 0, i);
			j = i;
			after = ft_substr2(line, j, ft_strlen(line));
			tmp = real_expand(after, env);
			line = ft_strjoin2(before, tmp);
			break ;
		}
		i++;
	}
	return (line);
}

static int	ft_len2(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa2(int n)
{
	char	*str;
	int		len;
	long	nb;

	nb = n;
	len = ft_len2(nb);
	str = malloc(len + 1);
	ft_lstadd_back_free(&g_v->adress, init_free(str));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (nb != 0)
	{
		str[len] = (nb % 10) + '0';
		nb = nb / 10;
		len--;
	}
	return (str);
}

char	*random_string(void)
{
	char		*str;
	static int	i;

	str = ft_strjoin2("/tmp/heredoc", ft_itoa2(i++));
	return (str);
}

int	*retur_nvalue(void)
{
	static int	retur_n;

	retur_n = -1;
	return (&retur_n);
}

void	signal_handler5(int signum)
{
	(void)signum;
	*retur_nvalue() = dup(0);
	close(0);
}

void	signal_heredoc_norme(void)
{
	dup2(*retur_nvalue(), 0);
	close(*retur_nvalue());
	signal(SIGINT, signal_handler_4);
	g_v->g_exit_code = 130;
	*retur_nvalue() = 10;
}

void	h_norme2(t_token **tmp, char *str)
{
	(*tmp)->value = "<";
	(*tmp)->type = TOKEN_REDIR_IN;
	(*tmp)->next->value = str;
	(*tmp)->next->type = TOKEN_FILE;
}

char	*end_of_file(t_token **tmp)
{
	char	*eof;

	if ((*tmp)->next->helper_flag == 1)
		eof = concatenation(*tmp);
	else
		eof = (*tmp)->next->value;
	return (eof);
}

void heredoc2(t_token **tmp, char **env)
{
	char	*line;
	int		fd_f;
	char	*str;
	char	*eof;

	str = random_string();
	fd_f = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	eof = end_of_file(tmp);
	line = readline("> ");
	ft_lstadd_back_free(&g_v->adress, init_free(line));
	while (line)
	{
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0 && \
			(ft_strlen(line) == ft_strlen(eof)))
				break ;
		if ((*tmp)->next->flag != 1 && (*tmp)->next->flag != 0)
			if (ft_strchr(line, '$') != NULL && g_v->g_flag == 0)
				line = expand_heredoc(line, env);
		ft_putendl_fd(line, fd_f);
		line = readline("> ");
		ft_lstadd_back_free(&g_v->adress, init_free(line));
	}
	h_norme2(tmp, str);
}

void	heredoc(t_token *token, char **env)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		signal(SIGINT, signal_heredoc);
		if (tmp->type == TOKEN_HEREDOC)
			heredoc2(&tmp, env);
		if (*retur_nvalue() != -1)
			signal_heredoc_norme();
		tmp = tmp->next;
	}
}
