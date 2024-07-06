/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:54:41 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/05 11:25:07 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_word(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	ft_lstadd_back_free(&g_v->adress, init_free(tmp));
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
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
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
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
