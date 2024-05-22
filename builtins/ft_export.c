/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:00:10 by monachit          #+#    #+#             */
/*   Updated: 2024/05/22 13:25:26 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_repetition(char *value, t_env *env)
{
    t_env *tmp = env;
    while (tmp)
    {
    if (value && ft_strncmp(value, tmp->value, ft_strlen(value)) == 0)
        return 0;
    tmp = tmp->next;
    }
    return 1;
}

char  **ft_export(t_node *node, char **env1)
{
    t_env *new;
    char *value;
    int i;
    new = malloc(sizeof(t_env));
    if (!new)
        return (0);
    new->next = NULL;
    new->value = env1[0];
    i = 1;
    while (env1[i])
    {
        value = env1[i];
        ft_lstadd_back2(&new, ft_lstnew2(value));
        i++;
    }
    i = 1;
    if(node->data->cmd->args[1] == NULL)
    {
        t_env *tmp = new;
        while(tmp)
        {
            printf("declare -x %s\n", tmp->value);
            tmp = tmp->next;
        }
        free(new);
        return env1;
    }
    while(check_repetition(node->data->cmd->args[i], new) && node->data->cmd->args[i])
    {
        value = node->data->cmd->args[i];
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