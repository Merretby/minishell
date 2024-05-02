/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/01 22:13:06 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_splitstring(char *str, t_list **words)
{
    char **s;
    int     i;
    
    s = ft_split(str, ' ');
    i = 0;
    while (s[i])
    {
        ft_lstadd_back(words, ft_lstnew(s[i]));
        i++;
    }
}

void    ft_lexer(t_list *words)
{
    int i;

    i = 0;
    while (words)
    {
        ft_first_check(words, i);
        words = words->next;
        i++;
    }
}

int main()
{
    char    *str;
    t_list  *words = NULL;
    str = readline("minishell > ");
    while (str)
    {
        add_history(str);
        ft_splitstring(str, &words);
        ft_lexer(words);
        str = readline("minishell > ");
    }
}