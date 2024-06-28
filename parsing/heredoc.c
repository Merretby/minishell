/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:44:32 by moer-ret          #+#    #+#             */
/*   Updated: 2024/06/28 22:58:26 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *concatenation(t_token *token, int *flaag)
{
	t_token *tmp;
	t_token *next;
	char 	*str;

	tmp = token;
	(*flaag) = 1;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
		{
			tmp = tmp->next;
			if (tmp->helper_flag == 1)
			{
				next = tmp->next;
				while (next && (next->type == TOKEN_ID || next->type == TOKEN_STRING))
				{
					str = ft_strjoin2(tmp->value, next->value);
					// free(tmp->value);
					tmp->value = str;
					tmp->helper_flag = tmp->next->helper_flag;
					tmp->next = tmp->next->next;
					// free(next->value);
					// free(next);
					next = tmp->next;
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

char *expand_heredoc(char *line, char **env)
{
	int i;
	int j;
	char *tmp;
	char *before;
	char *after;

	i = 0;
	while(line[i])
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
			// free(tmp);
			// free(before);
			// free(after);
			break;
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
	char			*str;
	static int		i;

	str = ft_strjoin2("/tmp/heredoc", ft_itoa2(i++));
	return (str);
}

int *retur_nvalue(void)
{
	static int retur_n = -1;
	
	return (&retur_n);
}

void signal_handler5(int signum)
{
	(void)signum;
	*retur_nvalue() = dup(0);
	close(0);
}


void	heredoc(t_token *token, char **env)
{
	int 	flaag;
	char 	*str;
	char	*line;
	char	*eof;
	t_token	*tmp;
	int		fd_f;


	flaag = 0;
	tmp = token;
	while (tmp)
	{
		signal(SIGINT, signal_heredoc);
		if (tmp->type == TOKEN_HEREDOC)
		{
			str = random_string();
			fd_f = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (tmp->next->helper_flag == 1)
				eof = concatenation(tmp, &flaag);
			else
				eof = tmp->next->value;
			line = readline("> ");
			ft_lstadd_back_free(&g_v->adress, init_free(line));
			while (line)
			{
				if (ft_strncmp(line, eof, ft_strlen(eof)) == 0 && \
					(ft_strlen(line) == ft_strlen(eof)))
					break ;
				if (tmp->next->flag != 1 && tmp->next->flag != 0)
				{
					if (ft_strchr(line, '$') != NULL && flaag == 0)
						line = expand_heredoc(line, env);
				}
				ft_putendl_fd(line, fd_f);
				// free (line);
				line = readline("> ");
				ft_lstadd_back_free(&g_v->adress, init_free(line));
			}
			tmp->value = "<";
			tmp->type = TOKEN_REDIR_IN;
			tmp->next->value = str;
			tmp->next->type = TOKEN_FILE;
			close(fd_f);
			// free(eof);
		}
		if (*retur_nvalue() != -1)
		{
			dup2(*retur_nvalue(), 0);
			close(*retur_nvalue());
			signal(SIGINT, signal_handler);
		}
		tmp = tmp->next;
	}
}
