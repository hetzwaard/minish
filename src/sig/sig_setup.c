/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sig_setup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/30 12:00:00 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/30 13:05:00 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sig_set_handler(void (*handler)(int))
{
	signal(SIGINT, handler);
}

static void	sig_set_signal_inner(int mode)
{
	if (mode == MAIN)
	{
		sig_set_handler(sigint_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC)
	{
		sig_set_handler(sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	sig_set_signal(int mode)
{
	if (mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == PARENT || mode == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		sig_set_signal_inner(mode);
}

void	sig_setup(void)
{
	sig_set_signal(MAIN);
}
