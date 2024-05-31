/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:46:16 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/05 15:46:53 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_token **token, t_lexer **lexer)
{
	t_token *tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		if (tmp->type == TOKEN_STRING || tmp->type == TOKEN_ID
			|| tmp->type == TOKEN_OUTFILE || tmp->type == TOKEN_FILE)
			free(tmp->value);
		free(tmp);
	}
	free(*lexer);

	lexer = NULL;
	token = NULL;
	return ;
}