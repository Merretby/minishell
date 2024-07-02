/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:00:56 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/01 21:15:48 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	ft_lstadd_back_free(&g_v->adress, init_free(tmp));
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i] && ft_isalnum(str[i]))
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*remove_word(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = ft_strlen(str);
	while (str[i] && ft_isalnum(str[i]))
		i++;
	tmp = (char *)malloc(sizeof(char) * (j - i + 1));
	ft_lstadd_back_free(&g_v->adress, init_free(tmp));
	if (!tmp)
		return (NULL);
	j = 0;
	while (str[i])
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*join_char(char *str, char c)
{
	char	*tmp;
	int		i;

	if (!str)
		str = ft_strdup1("");
	i = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	ft_lstadd_back_free(&g_v->adress, init_free(tmp));
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	return (tmp);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s1)
		s1 = "";
	if (!s1 || !s2)
		return (NULL);
	j = 0;
	i = -1;
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	ft_lstadd_back_free(&g_v->adress, init_free(ptr));
	if (!ptr)
		return (NULL);
	while (s1 && s1[++i])
		ptr[i] = s1[i];
	while (s2 && s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

char	*get_value(char *str, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], (str), ft_strlen(str)) == 0
			&& env[i][ft_strlen(str)] == '=')
		{
			tmp = ft_strchr(env[i], '=') + 1;
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

int	check_doller(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

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

char	*remove_space(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	str = change_tab(str);
	while (str[i])
		if (str[i++] == ' ')
			j++;
	tmp = (char *)malloc(sizeof(char) * (i - j + 2));
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

	(*loop_tmp)->value = remove_space((*loop_tmp)->value);
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
				if (ft_isalnum(loop_tmp->value[i + 1]))
				{
					handel_norme_expand(env, &loop_tmp, i);
					if (loop_tmp->value[0] == '\0')
						if (handel_norme_expand2(token, &loop_tmp))
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
