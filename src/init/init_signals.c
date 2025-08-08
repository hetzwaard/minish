/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_signals.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 22:39:18 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/08 22:39:18 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(EOF, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	signal_handler(int signum)
{
	g_signals = signum;
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		if (signum == SIGINT)
		{
			ft_printf("\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	return ;
}

void	init_signals(void)
{
	g_signals = 0;
	signal(SIGINT, signal_handler);
	signal(EOF, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
