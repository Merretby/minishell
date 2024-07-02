/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:06:29 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/02 13:46:27 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	concatenation_norme(t_token **tmp, t_token **next)
{
	char	*str;

	str = ft_strjoin2((*tmp)->value, (*next)->value);
	(*tmp)->value = str;
	(*tmp)->helper_flag = (*tmp)->next->helper_flag;
	(*tmp)->next = (*tmp)->next->next;
	(*next) = (*tmp)->next;
}

char	*concatenation(t_token *token)
{
	t_token	*tmp;
	t_token	*next;

	tmp = token;
	g_v->g_flag = 1;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
		{
			tmp = tmp->next;
			if (tmp->helper_flag == 1)
			{
				next = tmp->next;
				while (next && (next->type == TOKEN_ID
						|| next->type == TOKEN_STRING))
				{
					concatenation_norme(&tmp, &next);
					if (tmp->helper_flag == 0)
						return (tmp->value);
				}
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*expand_heredoc(char *line, char **env)
{
	int		i;
	int		j;
	char	*tmp;
	char	*before;
	char	*after;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			while (line[i] && line[i] != '$')
				i++;
			before = ft_substr2(line, 0, i);
			j = i;
			after = ft_substr2(line, j, ft_strlen(line));
			tmp = real_expand(after, env);
			line = ft_strjoin2(before, tmp);
			break ;
		}
		i++;
	}
	return (line);
}

char	*random_string(void)
{
	char		*str;
	static int	i;

	str = ft_strjoin2("/tmp/heredoc", ft_itoa2(i++));
	return (str);
}

char	*end_of_file(t_token **tmp)
{
	char	*eof;

	if ((*tmp)->next->helper_flag == 1)
		eof = concatenation(*tmp);
	else
		eof = (*tmp)->next->value;
	return (eof);
}
