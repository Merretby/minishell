/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:44:32 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/17 21:05:42 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc(t_node *tree)
{
	char *line;
	char *dilmiter;
	int fd[2];

	printf("---------->%d\n" , tree->flag_heredoc);
	if (tree->flag_heredoc == 1)
	{
		dilmiter = tree->right->data->cmd->value;
		line = readline("> ");
		while (line)
		{
			if (ft_strncmp(line, dilmiter, ft_strlen(dilmiter)) == 0 \
			&& ft_strlen(line) == ft_strlen(dilmiter))
				break ;
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
			line = readline("> ");
		}
		// unlink("/tmp/.heredoc");
	}
	return ;
}
