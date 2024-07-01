/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:44:50 by monachit          #+#    #+#             */
/*   Updated: 2024/06/30 13:27:49 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_node *tree)
{
	char	buffer[PATH_MAX];

	(void)tree;
	getcwd(buffer, PATH_MAX);
	printf("%s\n", buffer);
	return (1);
}
