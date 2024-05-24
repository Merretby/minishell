/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:00:56 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/24 17:40:30 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(char *str)
{
	int i;
	char *tmp;

	i = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '$')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '$')
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
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '$')
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

int find_doller(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			j++;
		i++;
	}
	return (j);
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

void	expand(t_token *token, char **env)
{
	char *str;
	char *tmp;
	int i;
	int doller;
	char *tmp2;

	i = 0;
	tmp2 = NULL;
	while (token)
	{
		if (ft_strchr(token->value, '$') != NULL)
		{
			doller = find_doller(token->value);
			while (doller > 0)
			{
				str = get_word(token->value + 1);
				token->value = remove_word(token->value + 1);
				printf("token %s\n", token->value);
				while (env[i])
				{
					if (ft_strncmp(env[i], (str), ft_strlen(str)) == 0 \
					&& env[i][ft_strlen(str)] == '=')
					{
						tmp = ft_strchr(env[i], '=') + 1;
						tmp2 = ft_strjoin2(tmp2, tmp);
						printf("tmp2:%s\n", tmp2);
						break;
					}
					i++;
				}
				doller--;
			}
			token->value = tmp2;
		}	
		token = token->next;
	}
}


// void expand(t_node *tree)
// {
// 	char **split;
// 	int a;
// 	int i;
// 	int k;
// 	int j;

// 	if (!tree)
// 		return ;
// 	i = 0;
// 	while (tree->data->cmd->args[i])
// 	{
// 		j = 0;
// 		while (tree->data->cmd->args[i][j])
// 		{
			// if (tree->data->cmd->args[i][j] == '$')
// 			{
// 				split = ft_split(tree->data->cmd->args[i], '$');
// 				a = 0;
// 				while (split[a])
// 				{
// 					k = 0;
// 					while (tree->env1 && tree->env1[k])
// 					{
// 						if (ft_strncmp(tree->env1[k], (split[a]), ft_strlen(split[a])) == 0 \
// 						&& tree->env1[k][ft_strlen(split[a])] == '=')
// 						{
// 							split[a] = ft_strchr(tree->env1[k], '=') + 1;
// 							break;
// 						}
// 						k++;
// 					}
// 					a++;
// 				}
// 				if (split[a] == NULL)
// 				{
// 					a = 0;
// 					if (split[a] && split[a + 1])
// 					{
// 						while (split[a] && split[a + 1])
// 						{
// 							if (a == 0)	
// 								tree->data->cmd->args[i] = ft_strjoin(split[a], split[a + 1]);
// 							else
// 								tree->data->cmd->args[i] = ft_strjoin(tree->data->cmd->args[i], split[a + 1]);
// 							a++;
// 						}
// 					}
// 					else
// 						tree->data->cmd->args[i] = split[a];
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
//  	expand(tree->left);
// 	expand(tree->right);
// }

// char	*get_word(char *str)
// {
// 	int i;
// 	char *tmp;

// 	i = 0;
// 	while (str[i] != '\0' && str[i] != ' ' && str[i] != '$')
// 		i++;
// 	tmp = (char *)malloc(sizeof(char) * (i + 1));
// 	if (!tmp)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] != '\0' && str[i] != ' ' && str[i] != '$')
// 	{
// 		tmp[i] = str[i];
// 		i++;
// 	}
// 	tmp[i] = '\0';
// 	return (tmp);
// }

// void	expand(t_node *tree)
// {
// 	int i;
// 	int j;
// 	int k;
// 	char *str;
// 	char *tmp;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	if (!tree)
// 		return ;
// 	str = ft_strdup("");
// 	while (tree->data->cmd->args[i])
// 	{
// 		j = 0;
// 		while (tree->data->cmd->args[i][j])
// 		{
// 			printf("args %c\n", tree->data->cmd->args[i][j]);
// 			if (tree->data->cmd->args[i][j] == '$')
// 			{
// 				tmp = get_word((tree->data->cmd->args[i] + j + 1));
// 				printf("tmp: %s\n", tmp);
// 				k = 0;
// 				while (tree->env1 && tree->env1[k])
// 				{
// 					if (ft_strncmp(tree->env1[k], (tmp), ft_strlen(tmp)) == 0 \
// 					&& tree->env1[k][ft_strlen(tmp)] == '=')
// 					{
// 						str = ft_strjoin(str, (ft_strchr(tree->env1[k], '=') + 1));
// 						printf("str: %s\n", str);
// 						break;
// 					}
// 					k++;
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}	
// 	expand(tree->left);
// 	expand(tree->right);
// }

		// if (ft_strchr(tree->data->cmd->args[i], '$') != NULL)
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