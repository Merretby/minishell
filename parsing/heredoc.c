/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:44:32 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/31 16:17:06 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *concatenation(t_token *token, int *flaag)
{
	t_token *tmp;
	char 	*str;

	tmp = token;
	(*flaag) = 1;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
		{
			tmp = tmp->next;
			while (tmp && tmp->helper_flag == 1)
			{
				str = ft_strjoin(tmp->value, tmp->next->value);
				if (tmp->next && tmp->next->helper_flag == 1)
				{
					tmp = tmp->next;
					str = ft_strjoin(str, tmp->next->value);
				}
				tmp->next->value = str;
				if (tmp->next && tmp->next->helper_flag != 1)
					return (tmp->next->value);
				tmp = tmp->next;
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

	j = 0;
	i = 0;
	while(line[i])
	{
		if (line[i] == '$')
		{
			while (line[i] && line[i] != '$')
				i++;
			before = ft_substr(line, j, i);
			j = i;
			after = ft_substr(line, j, ft_strlen(line));
			tmp = real_expand(after, env);
			line = ft_strjoin(before, tmp);
			break;
		}
		i++;
	}
	return (line);
}

void	heredoc(t_token *token, char **env)
{
	int 	flaag;
	char	*line;
	char	*eof;
	t_token	*tmp;
	int		fd_f;

	flaag = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
		{
			fd_f = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (tmp->next->helper_flag == 1)
				eof = concatenation(tmp, &flaag);
			else
				eof = tmp->next->value;
			printf("%s\n", eof);
			line = readline("> ");
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
				free (line);
				line = readline("> ");
			}
			tmp->value = ft_strdup("<");
			tmp->type = TOKEN_REDIR_IN;
			tmp->next->value = ft_strdup("/tmp/heredoc");
			tmp->next->type = TOKEN_FILE;
		}
		tmp = tmp->next;
	}
}
