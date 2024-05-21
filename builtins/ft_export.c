/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:00:10 by monachit          #+#    #+#             */
/*   Updated: 2024/05/21 17:18:12 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char  **ft_export(t_node *node, char **env1)
{
    t_env *new;
    char *value;
    int i;
    new = malloc(sizeof(t_env));
    if (!new)
        return (0);
    new->next = NULL;
    new->value = ft_strjoin("declare -x ", env1[0]);
    i = 1;
    while (env1[i])
    {
        value = ft_strjoin("declare -x ", env1[i]);
        ft_lstadd_back2(&new, ft_lstnew2(value));
        i++;
    }
    i = 1;
    if(node->data->cmd->args[1] == NULL)
    {
        while(new)
        {
            printf("%s\n", new->value);
            new = new->next;
        }
        return env1;
    }
    while(node->data->cmd->args[i])
    {
        value = ft_strjoin("declare -x ", node->data->cmd->args[i]);
        ft_lstadd_back2(&new, ft_lstnew2(value));
        i++;
    }
    t_env *tmp = new;
    i = 0;
    while (tmp) {
        env1[i++] = tmp->value;
        t_env *to_free = tmp;
        tmp = tmp->next;
        free(to_free);
    }
    env1[i] = NULL;

    return env1;
}
