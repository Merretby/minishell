/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:51:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/06 16:58:27 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_cmd(t_token *token)
{
	t_cmd *cmd;
	char *tmp;

	cmd = init_cmd(token->value);
	token = token->next;
	while (token  && (token->type == TOKEN_ID || token->type == TOKEN_STRING))
	{
		cmd->cmd = ft_strjoin(cmd->cmd, " ");
		tmp = cmd->cmd;
		if (token)
		{
			cmd->cmd = ft_strjoin(tmp, token->value);
			free(tmp);
		}
		token = token->next;
	}
	printf("%s\n", cmd->cmd);
}

// void	print_cmd(t_cmd *cmd)
// {
// 	while (cmd)
// 	{
// 		printf("%s\n", cmd->cmd);
// 		cmd = cmd->next;
// 	}
// }