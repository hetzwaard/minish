/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sig_handlers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/30 12:00:00 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/30 12:00:00 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "../../include/minishell.h"

/*
** SIGINT handler for interactive prompt.
*/
void	sigint_prompt(int signum)
{
	(void)signum;
	g_signals = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
** SIGINT handler for heredoc child. Exits with 130.
*/
void	sigint_heredoc(int signum)
{
	(void)signum;
	g_signals = 130;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}
