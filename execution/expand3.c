/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:54:53 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/04 17:07:25 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_tab(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
	tmp = ft_strdup1(str);
	return (tmp);
}

char	*remove_space(char *str, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	str = change_tab(str);
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
			j++;
		i++;
	}
	tmp = (char *)malloc(sizeof(char) * (i - j + 1));
	ft_lstadd_back_free(&g_v->adress, init_free(tmp));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			tmp[j++] = str[i];
		if (str[i] == ' ' && str[i + 1] != ' ')
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	insert_after(t_token *node, char *value)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	ft_lstadd_back_free(&g_v->adress, init_free(new_node));
	new_node->value = ft_strdup1(value);
	new_node->next = node->next;
	new_node->type = TOKEN_ID;
	new_node->flag = -1;
	new_node->helper_flag = -1;
	node->next = new_node;
}

char	*befor_str(char *value, int i, char	**env)
{
	char	*str;
	char	*befor;
	char	*after;
	int		j;

	j = 0;
	befor = ft_substr2(value, j, i);
	j = i;
	after = ft_substr2(value, j, ft_strlen(value));
	str = real_expand(after, env);
	return (ft_strjoin2(befor, str));
}

void	loop_value(t_token **loop_tmp, int k)
{
	t_token	*helper;
	char	**argument;

	(*loop_tmp)->value = remove_space((*loop_tmp)->value, 0);
	if (ft_strchr((*loop_tmp)->value, ' ') != NULL)
	{
		helper = (*loop_tmp);
		argument = ft_split1((*loop_tmp)->value, ' ');
		while (argument[k])
		{
			insert_after((*loop_tmp), argument[k]);
			(*loop_tmp) = (*loop_tmp)->next;
			k++;
		}
		helper->value = argument[0];
	}
}
