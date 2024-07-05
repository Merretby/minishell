/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:00:56 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/05 12:21:13 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*real_expand(char *line, char **env)
{
	int		i;
	char	*str;
	char	*tmp2;

	i = 0;
	tmp2 = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			str = get_word(line + 1);
			line = remove_word(line + 1);
			if (get_value(str, env) != NULL)
				tmp2 = ft_strjoin2(tmp2, get_value(str, env));
			if (check_doller(line) == 1)
				if (line[0] != '$' && line[0] != '\\' && !ft_isdigit(line[0]))
					tmp2 = join_char(tmp2, line[0]);
			i = -1;
		}
		i++;
	}
	if (line != NULL)
		tmp2 = ft_strjoin2(tmp2, line);
	return (tmp2);
}

void	handel_norme_expand(char **env, t_token **loop_tmp, int i)
{
	while ((*loop_tmp)->value[i] != '$' && (*loop_tmp)->value[i])
		i++;
	(*loop_tmp)->value = befor_str((*loop_tmp)->value, i, env);
	if ((*loop_tmp)->flag != 1)
		loop_value(loop_tmp, 1);
}

int	handel_norme_expand2(t_token **token, t_token **loop_tmp)
{
	t_token	*tmp;

	tmp = (*loop_tmp);
	(*loop_tmp) = (*loop_tmp)->next;
	delete_node(token, tmp);
	if (loop_tmp)
		return (1);
	return (0);
}

int	normeinet(t_token *loop_tmp, int i)
{
	if (ft_isalnum(loop_tmp->value[i + 1]) || loop_tmp->value[i + 1] == '_')
		return (1);
	return (0);
}

void	expand(t_token **token, char **env, int i)
{
	t_token	*loop_tmp;

	loop_tmp = *token;
	while (loop_tmp)
	{
		i = 0;
		while (loop_tmp->value && loop_tmp->value[i])
		{
			if (loop_tmp->value[i] == '$' && loop_tmp->flag != 0)
			{
				if (normeinet(loop_tmp, i))
				{
					handel_norme_expand(env, &loop_tmp, i);
					if (loop_tmp->value[0] == '\0')
						if (handel_norme_expand2(token, &loop_tmp) && \
							(loop_tmp && loop_tmp->value != NULL))
							continue ;
					break ;
				}
			}
			i++;
		}
		if (loop_tmp && loop_tmp->value != NULL)
			loop_tmp = loop_tmp->next;
	}
}
