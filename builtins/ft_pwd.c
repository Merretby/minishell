/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:44:50 by monachit          #+#    #+#             */
/*   Updated: 2024/05/18 14:39:18 by monachit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(t_node *tree)
{
    (void)tree;
    char buffer[PATH_MAX];

    getcwd(buffer, PATH_MAX);
    printf("%s\n", buffer);
    return (1);
}