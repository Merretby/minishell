/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:00:10 by monachit          #+#    #+#             */
/*   Updated: 2024/05/25 15:29:38 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_repetition(t_env **env1, char *value)
{
    t_env *tmp = *env1;
    char *tmp2;
    while (tmp)
    {
        tmp2 = ft_substr(value, 0, ft_strchr(value, '=') - value);
        if (!ft_strncmp(tmp->value, tmp2, ft_strlen(tmp2)))
        {
            free(tmp->value);
            tmp->value = ft_strdup(value);
            free(tmp2);
            return 1;
        }
        free(tmp2);
        tmp = tmp->next;
    }
    return 0;
}

char *ft_init_export(char *value)
{
    char *new_env;
    char *tmp;
    int i;

    i = 0;
    while (value[i] && value[i] != '=')
        i++;
    new_env = ft_substr(value, 0, i + 1);
    if (value[i + 1] != '\"' && value[i + 1] != '\'')
        new_env = ft_strjoin(new_env, "\"");
    tmp = ft_strjoin(new_env, value + i + 1);
    free(new_env);
    if (tmp[ft_strlen(tmp) - 1] != '\"' && tmp[ft_strlen(tmp) - 1] != '\'')
        tmp = ft_strjoin(tmp, "\"");
    return (tmp);
}

char *check_value(char *value)
{
    char *tmp;
    char *tmp2;
    int i;

    i = 0;
    while (value[i] && value[i] != '=')
        i++;
    if (ft_strlen(value) == i)
    {
        value = ft_strjoin(value, "=");
        value = ft_strjoin(value, "\'\'");
        return value;
    }
    else
    {
        tmp = ft_substr(value, 0, i + 1);
        if (value[i + 1] != '\"')
            tmp = ft_strjoin(tmp, "\"");
        tmp2 = ft_strjoin(tmp, value + i + 1);
        free(tmp);
        tmp2 = ft_strjoin(tmp2, "\"");
        return tmp2;
    }
    return value;
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
    new->value = ft_init_export(env1[0]);
    i = 1;
    if (node->data->cmd->args[1] && node->data->cmd->args[1][0] == '=')
    {
        printf("minishell: export: `%s': not a valid identifier\n", node->data->cmd->args[1]);
        return env1;
    }
    while (env1[i])
    {
        value = env1[i];
        ft_lstadd_back2(&new, ft_lstnew2(ft_init_export(value)));
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
    while(node->data->cmd->args[i])
    {
        if (check_repetition(&new, node->data->cmd->args[i]))
            i++;
        else
        {
            value = node->data->cmd->args[i];
            value = check_value(value);
            ft_lstadd_back2(&new, ft_lstnew2(value));
            i++;
        }
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