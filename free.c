/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:46:16 by mnachit           #+#    #+#             */
/*   Updated: 2024/06/02 18:04:12 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_token **token, t_lexer **lexer)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = *token;
		printf("free token->value: %s\n", tmp->value);
		*token = (*token)->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	free(*lexer);

	lexer = NULL;
	token = NULL;
}