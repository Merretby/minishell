/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:00:10 by monachit          #+#    #+#             */
/*   Updated: 2024/07/05 12:20:54 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_add(t_env **new, char *str)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
			break ;
		i++;
	}
	if (i != ft_strlen(str))
	{
		if (!str[i + 2])
			return (1);
		else if (check_repetition2(new, str, i + 2))
			return (1);
		else
		{
			tmp = ft_strjoin2(ft_substr2(str, 0, i), "=");
			str = ft_strjoin2(tmp, str + i + 2);
			ft_lstadd_back2(new, ft_lstnew2(str));
			return (1);
		}
	}
	return (0);
}

void	ft_inisialize_node(t_env **new, char **env1)
{
	size_t	i;

	i = 0;
	while (env1[i])
	{
		ft_lstadd_back2(new, ft_lstnew2(env1[i]));
		i++;
	}
}

int	check_error(char *s)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
	{
		ft_print_error_export(s);
		return (1);
	}
	while (s[i])
	{
		if ((s[i] == '=') || (s[i] == '+' && s[i + 1] && s[i + 1] == '='))
			break ;
		i++;
	}
	tmp = ft_substr2(s, 0, i);
	i = 0;
	while (tmp[i])
	{
		if (!ft_isalnum(tmp[i]) && tmp[i] != '_')
			return (ft_print_error_export(s), 1);
		i++;
	}
	return (0);
}

void	ft_export2(t_node *node, t_env **new)
{
	char	*value;
	size_t	i;

	i = 1;
	while (node->data->cmd->args[i])
	{
		if (check_error(node->data->cmd->args[i]))
			i++;
		else if (check_add(&(*new)->next, node->data->cmd->args[i]))
			i++;
		else if (check_repetition(&(*new)->next, node->data->cmd->args[i]))
			i++;
		else
		{
			value = node->data->cmd->args[i];
			ft_lstadd_back2(new, ft_lstnew2(value));
			i++;
		}
	}
}

char	**ft_export(t_node *node, char **env1)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	ft_lstadd_back_free(&g_v->adress, init_free(new));
	if (!new)
		return (0);
	new->next = NULL;
	new->value = NULL;
	if (node->data->cmd->args[1] && node->data->cmd->args[1][0] == '=')
		return (ft_print_error_export(node->data->cmd->args[1]), env1);
	ft_inisialize_node(&new, env1);
	if (node->data->cmd->args[1] == NULL)
	{
		ft_printexport(new->next);
		return (env1);
	}
	ft_export2(node, &new);
	env1 = ft_env1(env1, new);
	return (env1);
}
