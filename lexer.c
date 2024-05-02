/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:43:59 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/02 14:48:58 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_addto_newlist(char *str, int i, char c)
{
    Token *token = ft_lstnew(str);
    if (token)
    {
        token->type = c;
        ft_lstadd_back(&token, ft_lstnew(str));
    }
}

void ft_check_words(char *str, int i);
{
    
}

void ft_first_check(t_list *words, int i)
{
    if (ft_strncmp(words->content, ">", 1) == 0)
        ft_addto_newlist(">", i, REDIR_OUT);
    else if (ft_strncmp(words->content, " ", 1) == 0)
        ft_addto_newlist(" ", i, WHITE_SPACE);
    else if (ft_strncmp(words->content, "\n", 1) == 0)
        ft_addto_newlist("\n", i, NEW_LINE);
    else if (ft_strncmp(words->content, "'", 2) == 0)
        ft_addto_newlist("'", i, QOUTE);
    else if (ft_strncmp(words->content, "\"", 2) == 0)
        ft_addto_newlist("\"", i, DOUBLE_QUOTE);
    else if (ft_strncmp(words->content, "\\", 2) == 0)
        ft_addto_newlist("\\", i, ESCAPE);
    else if (ft_strncmp(words->content, "$", 1) == 0)
        ft_addto_newlist("$", i, ENV);
    else if (ft_strncmp(words->content, "|", 1) == 0)
        ft_addto_newlist("|", i, PIPE_LINE);
    else if (ft_strncmp(words->content, "<", 1) == 0)
        ft_addto_newlist("<", i, REDIR_IN);
    else
        ft_check_words(words->content, i);
}
