/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:20:03 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/28 20:57:39 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	sig_int(int sig)
{
	if (g_lobal_var == HERE_DOC)
	{
		write(1, "\n", 1);
		ft_putstr_fd("\r\033[2K\033[1A", 1);
		rl_replace_line("", 0);
	}
	else
	{
		g_lobal_var = sig;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ignor_signal_perent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handel_signal(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}
