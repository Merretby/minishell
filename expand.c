/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:00:56 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/23 12:57:49 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp2(char *s1, char *s2, int n)
{
	int			i;

	i = 0;
	i = 0;
	if (s1 == NULL || s2 == NULL)
	{
		printf("error\n");
		return (-1);
	}
	while (i < n && ((unsigned char)s1[i] || (unsigned char)s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int ft_strlen2(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	expand(t_node *tree)
{
	int i;
	int j;
	int k;
	char *tmp;

	i = 0;
	j = 0;
	k = 0;
	if (!tree)
		return ;
	while (tree->data->cmd->args[i])
	{
		j = 0;
		while (tree->data->cmd->args[i][j] != '\0')
		{
			if (tree->data->cmd->args[i][j] == '$' && tree->data->cmd->s_f != 1)
			{
				tmp = tree->data->cmd->args[i] + j + 1;
				k = 0;
				while (tree->env1 && tree->env1[k])
				{
					if (ft_strncmp2(tree->env1[k], (tmp), ft_strlen2(tmp)) == 0 \
					&& tree->env1[k][ft_strlen2(tmp)] == '=')
					{
						tree->data->cmd->args[i] = (ft_strchr(tree->env1[k], '=') + 1);
						break;
					}
					k++;
				}
			}
			j++;
		}
		i++;
	}	
	expand(tree->left);
	expand(tree->right);
}

		// if (ft_strchr(tree->data->cmd->args[i], '$') != NULL && tree->data->cmd->s_f != 1)
		// {
		// 	tmp = tree->data->cmd->args[i + 1];
		// 	while (tree->env1[j])
		// 	{
				// if (ft_strncmp(tree->env1[j], (tmp),\
				//  ft_strlen(tmp)) == 0)
		// 			tree->data->cmd->args[i] = ft_strchr(tree->env1[j], '=');
		// 		j++;
		// 	}
		// }