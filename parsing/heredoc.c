/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:44:32 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/20 17:40:33 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc(t_token *token)
{
	char 	*str;
	char 	*line;
	char 	*eof;
	t_token	*tmp;
	int fd_f;

	tmp = token;
	fd_f = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
		{
			if (tmp->next->helper_flag == 1)
			{
				tmp = tmp->next;
				while (tmp && tmp->helper_flag == 1)
				{
					str = ft_strjoin(tmp->value, tmp->next->value);
					tmp->value = str;
					if (tmp->next->helper_flag != 1)
						break;
					tmp = tmp->next;
				}
				eof = tmp->value;
				printf("eof: %s\n", eof);
			}
			else
				eof = tmp->next->value;
			while (line)
			{
				line = readline(">");
				if (ft_strncmp(line, eof, ft_strlen(eof)) == 0 && \
					ft_strlen(line) == ft_strlen(eof))
					break ;
				ft_putendl_fd(line, fd_f);
				free (line);
			}
		}
		tmp = tmp->next;
	}
}
