/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:56:15 by mnachit           #+#    #+#             */
/*   Updated: 2024/07/04 13:22:45 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_2(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	g_v->g_exit_code = 130;
}

void	signal_handler_child(int signum)
{
	(void)signum;
	g_v->g_exit_code = 130;
}

void	signal_heredoc(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDOUT_FILENO);
	*retur_nvalue() = dup(0);
	close(0);
}

void	signal_handler_4(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_quit(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
}
