/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:00:10 by monachit          #+#    #+#             */
/*   Updated: 2024/06/08 14:54:28 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_repetition(t_env **env1, char *value)
{
    t_env *tmp = *env1;
    char *tmp2;
    int i;

    while (tmp)  // export a=1 a=2
    {
        i = 0;
        while (tmp->value[i] && tmp->value[i] != '=')
            i++;
        tmp2 = ft_substr(tmp->value, 0, i);
        if (ft_strcmp(tmp2, ft_substr(value, 0, i)) == 0)
        {
            // free(tmp->value);
            i = 0;
            while (value[i] && value[i] != '=')
                i++;
            if (value[i]) 
                tmp->value = ft_strdup(value);
            // free(tmp2);
            return 1;
        }
        //free(tmp2);
        tmp = tmp->next;
    }
    return 0;
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

void ft_printexport(t_env *new)
{
    char    *tmp;
    int i;

    while (new)
    {
        i = 0;
        while (new->value[i] && new->value[i] != '=')
            i++;
        if (new->value[i] == '\0')
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
int check_repetition2(t_env **new, char *value , int k)
{
    t_env *tmp = *new;
    char *tmp2;
    int i;

    while (tmp)
    {
        i = 0;
        while (tmp->value[i] && tmp->value[i] != '=')
            i++;
        tmp2 = ft_substr(tmp->value, 0, i);
        if (ft_strcmp(tmp2, ft_substr(value, 0, i)) == 0)
        {
            tmp->value = ft_strjoin(tmp->value, ft_substr(value, k, ft_strlen(value) - k));
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

int check_add(t_env **new, char *str)
{
    char *tmp;
    size_t i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
            break;
        i++;
    }
    if (i != ft_strlen(str))
    {
        if (!str[i + 2])
            return 1;
        else if(check_repetition2(new, str , i + 2))
            return 1;
        else
        {
            tmp = ft_strjoin(ft_substr(str, 0, i),  "=");
            str = ft_strjoin(tmp, str + i + 2);
            ft_lstadd_back2(new, ft_lstnew2(str));
            return 1;
        }
    }
    return 0;
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
    if (node->data->cmd->args[1] && node->data->cmd->args[1][0] == '=')
    {
        printf("minishell: export: `%s': not a valid identifier\n", node->data->cmd->args[1]);
        return env1;
    }
    while (env1[i])
    {
        value = env1[i];
        ft_lstadd_back2(&new, ft_lstnew2(value));
        i++;
    }
    i = 1;
    if(node->data->cmd->args[1] == NULL)
    {
        ft_printexport(new);
        free(new);
        return env1;
    }
    while(node->data->cmd->args[i])
    {
        if (check_add(&new, node->data->cmd->args[i]))
            i++;
        else if (check_repetition(&new, node->data->cmd->args[i]))
            i++;
        else
        {
            value = node->data->cmd->args[i];
            ft_lstadd_back2(&new, ft_lstnew2(value));
            i++;
        }
    }
    t_env *tmp = new;
    i = 0;
    while (tmp)
    {
        env1[i++] = tmp->value;
        t_env *to_free = tmp;
        tmp = tmp->next;
        free(to_free);
    }
    env1[i] = NULL;

    return env1;
}
