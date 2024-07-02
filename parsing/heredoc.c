/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:44:32 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/02 13:57:43 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	heredoc2(t_token **tmp, char **env)
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
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0 \
			&& (ft_strlen(line) == ft_strlen(eof)))
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
