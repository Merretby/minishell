/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:58:43 by monachit          #+#    #+#             */
/*   Updated: 2024/07/02 09:03:47 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	take_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}

int	ft_env(char **env)
{
	take_env(env);
	return (0);
}
