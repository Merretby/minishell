/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:20:04 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/05 12:45:34 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_cd(char *str)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	ft_print_error_export(char *s)
{
	ft_putstr_fd("minishell~$42: export: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	ft_check_mini(t_node *tree)
{
	if (!ft_strcmp(tree->data->cmd->args[0], "./minishell"))
	{
		signal(SIGINT, signal_handler_child);
		signal(SIGQUIT, SIG_IGN);
	}
}

int	ft_check_cd(char **env)
{
	char	*tmp;

	tmp = get_env(env, 5);
	if (chdir(tmp) == -1)
	{
		if (!tmp)
			ft_putstr_fd("minishell~$42: cd: HOME not set\n", 2);
		else
			error_cd(tmp);
		return (1);
	}
	return (0);
}
