/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:44:32 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/21 15:13:04 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *concatenation(t_token *token)
{
	t_token *tmp;
	char 	*str;

	tmp = token;
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

void	heredoc(t_token *token)
{
	char	*line;
	char	*eof;
	t_token	*tmp;
	int		fd_f;

	tmp = token;
	fd_f = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
		{
			if (tmp->next->helper_flag == 1)
				eof = concatenation(tmp);
			else
				eof = tmp->next->value;
			line = readline("> ");
			while (line)
			{
				if (ft_strncmp(line, eof, ft_strlen(eof)) == 0 && \
					(ft_strlen(line) == ft_strlen(eof)))
					break ;
				ft_putendl_fd(line, fd_f);
				free (line);
				line = readline("> ");
			}
		}
		tmp = tmp->next;
	}
}
