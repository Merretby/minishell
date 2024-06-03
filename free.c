/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:46:16 by mnachit           #+#    #+#             */
/*   Updated: 2024/06/03 16:22:12 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_token **token, t_lexer **lexer)
{
	t_token	*head;
	t_token	*tmp;

	head = *token;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	*token = NULL;
	free(*lexer);
}