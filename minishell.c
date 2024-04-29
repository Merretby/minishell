/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:18:33 by moer-ret          #+#    #+#             */
/*   Updated: 2024/04/29 15:41:03 by mnachit          ###   ########.fr       */
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

int main()
{
    char    *str;
    t_list  *words;
    str = readline("minishell > ");
    while (str)
    {
        ft_splitstring(str, &words);
        str = readline("minishell > ");
    }
}