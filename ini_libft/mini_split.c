/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:39:26 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/05 10:38:19 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_nachit(char const s, char c)
{
	if ((char )s == c)
		return (1);
	else
		return (0);
}

static int	ft_len(char const *s, char c)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (ft_nachit((s[i]), c) == 1)
			i++;
		else if (ft_nachit(s[i], c) == 0)
		{
			while (s[i] != c && s[i])
				i++;
			j++;
		}
	}
	return (j);
}

static char	**ft_daym(char const *s, char **str, char c, size_t length)
{
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	end = 0;
	while (i < length)
	{
		while (s[start] == c && s[start])
			start++;
		end = start;
		while (s[end] != c && s[end])
			end++;
		str[i] = ft_substr2(s, start, end - start);
		if (!str[i])
			return (NULL);
		i++;
		start = end;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split1(char const *s, char c)
{
	char	**str;
	size_t	length;

	if (!s)
		return (NULL);
	length = ft_len(s, c);
	str = malloc((length + 1) * sizeof(char *));
	ft_lstadd_back_free(&g_v->adress, init_free(str));
	if (!str)
		return (NULL);
	return (ft_daym(s, str, c, length));
}
