/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:44:50 by monachit          #+#    #+#             */
/*   Updated: 2024/06/25 10:16:17 by moer-ret         ###   ########.fr       */
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