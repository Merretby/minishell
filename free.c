/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:46:16 by mnachit           #+#    #+#             */
/*   Updated: 2024/06/05 15:12:11 by moer-ret         ###   ########.fr       */
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

void	free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}