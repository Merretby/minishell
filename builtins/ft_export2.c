/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:23:23 by mnachit           #+#    #+#             */
/*   Updated: 2024/07/01 14:32:07 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_repetition(t_env **env1, char *value)
{
	t_env	*tmp;
	char	*tmp2;
	int		i;

	tmp = *env1;
	while (tmp && tmp->value)
	{
		i = 0;
		while (tmp->value[i] && tmp->value[i] != '=')
			i++;
		tmp2 = ft_substr(tmp->value, 0, i);
		if (ft_strcmp(tmp2, ft_substr(value, 0, i)) == 0)
		{
			i = 0;
			while (value[i] && value[i] != '=')
				i++;
			if (value[i])
				tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*check_value(char *value)
{
	char	*tmp;
	char	*tmp2;
	size_t	i;

	i = 0;
	while (value[i] && value[i] != '=')
		i++;
	if (ft_strlen(value) == i)
	{
		value = ft_strjoin(value, "=");
		value = ft_strjoin(value, "\'\'");
		return (value);
	}
	else
	{
		tmp = ft_substr(value, 0, i + 1);
		if (value[i + 1] != '\"')
			tmp = ft_strjoin(tmp, "\"");
		tmp2 = ft_strjoin(tmp, value + i + 1);
		free(tmp);
		tmp2 = ft_strjoin(tmp2, "\"");
		return (tmp2);
	}
	return (value);
}

char	**ft_env1(char **env1, t_env *new)
{
	t_env	*tmp;
	int		i;
	t_env	*to_free;

	tmp = new->next;
	i = 0;
	while (tmp)
	{
		env1[i++] = tmp->value;
		to_free = tmp;
		tmp = tmp->next;
	}
	env1[i] = NULL;
	return (env1);
}

int	check_repetition2(t_env **new, char *value, int k)
{
	t_env	*tmp;
	char	*tmp2;
	int		i;

	tmp = *new;
	while (tmp && tmp->value)
	{
		i = 0;
		while (tmp->value[i] && tmp->value[i] != '=')
			i++;
		tmp2 = ft_substr(tmp->value, 0, i);
		if (ft_strcmp(tmp2, ft_substr(value, 0, i)) == 0)
		{
			free(tmp2);
			if (ft_strchr(tmp->value, '=') == NULL)
				tmp->value = ft_strjoin(tmp->value, "=");
			tmp->value = ft_strjoin(tmp->value, ft_substr(value, k,
						ft_strlen(value) - k));
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_printexport(t_env *new)
{
	char	*tmp;
	int		i;

	while (new && new->value)
	{
		i = 0;
		while (new->value[i] && new->value[i] != '=')
			i++;
		if (new->value && new->value[i] == '\0')
			printf("declare -x %s\n", new->value);
		else
		{
			tmp = ft_substr(new->value, 0, i);
			printf("declare -x %s=\"", tmp);
			free(tmp);
			tmp = ft_substr(new->value, i + 1, ft_strlen(new->value) - i - 1);
			printf("%s\"\n", tmp);
		}
		new = new->next;
	}
}
