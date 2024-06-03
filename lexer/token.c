/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:38:13 by moer-ret          #+#    #+#             */
/*   Updated: 2024/06/02 14:02:05 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_token(int type, char *value, char c)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	if (c == '"')
		token->flag = 1;
	else if (c == '\'')
		token->flag = 0;
	else
		token->flag = -1;
	token->helper_flag = 0;
	token->next = NULL;
	token->prev = NULL;
	token->args = NULL;
	token->arg = NULL;
	return (token);
}
