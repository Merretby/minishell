/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:00:56 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/31 23:11:56 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(char *str)
{
	int i;
	char *tmp;

	i = 0;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || \
	(str[i] >= 'A' && str[i] <= 'Z')))
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || \
	(str[i] >= 'A' && str[i] <= 'Z')))
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*remove_word(char *str)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = ft_strlen(str);
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || \
	(str[i] >= 'A' && str[i] <= 'Z')))
		i++;
	tmp = (char *)malloc(sizeof(char) * (j - i + 1));
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

char *join_char(char *str, char c)
{
	char *tmp;
	int i;

	if (!str)
		str = ft_strdup("");
	i = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
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
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	j = 0;
	i = -1;
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	while (s1 && s1[++i])
		ptr[i] = s1[i];
	while (s2 && s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

char *get_value(char *str, char **env)
{
	int i;
	char *tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], (str), ft_strlen(str)) == 0 \
		&& env[i][ft_strlen(str)] == '=')
		{
			tmp = ft_strchr(env[i], '=') + 1;
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

int check_doller(char *str)
{
	int i;

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
	int i;
	char *str;
	char *tmp2;

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

void	expand(t_token *token, char **env)
{
	int i;
	int j;
	// t_token *tmp;
	char *str;
	char *befor;
	char *after;

	j = 0;
	while (token)
	{
		i = 0;
		while (token->value && token->value[i])
		{
			if (token->value[i] == '$' && token->flag != 0)
			{
				while (token->value[i] != '$' && token->value[i])
					i++;
				befor = ft_substr(token->value, j, i);
				j = i;
				after = ft_substr(token->value, j, ft_strlen(token->value));
				str = real_expand(after, env);
				free(token->value);
				token->value = ft_strjoin2(befor, str);
				break;
			}
			i++;
		}	
		token = token->next;
	}
}
