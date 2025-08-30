/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sig_sigint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/30 12:00:00 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/30 12:00:00 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_prompt(int signum)
{
	(void)signum;
	g_signals = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_heredoc(int signum)
{
	(void)signum;
	g_signals = 130;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}
