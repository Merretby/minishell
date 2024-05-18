/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:44:50 by monachit          #+#    #+#             */
/*   Updated: 2024/05/18 12:53:55 by monachit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_node *tree)
{
    char buffer[PATH_MAX];

    get_cwd(buffer, PATH_MAX);
    printf("%s\n", buffer);
    return (1);
}