/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:44:32 by moer-ret          #+#    #+#             */
/*   Updated: 2024/06/04 20:15:37 by moer-ret         ###   ########.fr       */
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
					str = ft_strjoin(tmp->value, next->value);
					free(tmp->value);
					tmp->value = str;
					tmp->helper_flag = tmp->next->helper_flag;
					tmp->next = tmp->next->next;
					free(next->value);
					free(next);
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
			before = ft_substr(line, 0, i);
			j = i;
			after = ft_substr(line, j, ft_strlen(line));
			tmp = real_expand(after, env);
			line = ft_strjoin(before, tmp);
			free(tmp);
			free(before);
			free(after);
			break;
		}
		i++;
	}
	return (line);
}

char	*random_string(void)
{
	char			*str;
	static int		i;

	str = ft_strjoin("/tmp/heredoc", ft_itoa(i++));
	return (str);
}

void signal_handler4(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_code = 130;
		printf("\n");
		    rl_on_new_line();
   		 rl_replace_line("", 0);
    rl_redisplay();
	}
}

void	heredoc(t_token *token, char **env)
{
	int 	flaag;
	char 	*str;
	char	*line;
	char	*eof;
	t_token	*tmp;
	int		fd_f;

	signal(SIGINT, SIG_DFL);
	signal(SIGINT, signal_handler4);
	flaag = 0;
	tmp = token;
	while (tmp)
	{
		if (g_exit_code == 130)
			return ;
		if (tmp->type == TOKEN_HEREDOC)
		{
			str = random_string();
			fd_f = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (tmp->next->helper_flag == 1)
				eof = concatenation(tmp, &flaag);
			else
				eof = tmp->next->value;
			line = readline("> ");
			while (line)
			{
				if (g_exit_code == 130)
				{
					printf("THE END\n");
					return ;
				}
				if (ft_strncmp(line, eof, ft_strlen(eof)) == 0 && \
					(ft_strlen(line) == ft_strlen(eof)))
					break ;
				if (tmp->next->flag != 1 && tmp->next->flag != 0)
				{
					if (ft_strchr(line, '$') != NULL && flaag == 0)
						line = expand_heredoc(line, env);
				}
				ft_putendl_fd(line, fd_f);
				free (line);
				line = readline("> ");
			}
			tmp->value = "<";
			tmp->type = TOKEN_REDIR_IN;
			tmp->next->value = str;
			tmp->next->type = TOKEN_FILE;
			free(eof);
		}
		tmp = tmp->next;
	}
}
