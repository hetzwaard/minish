/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sig_pipex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/30 12:18:00 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/30 12:18:00 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sig_child(void)
{
	sig_set_signal(CHILD);
}

static int	sig_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	sig_pipex(int left_pid, int right_pid)
{
	int	left_status;
	int	right_status;

	sig_set_signal(PARENT);
	if (waitpid(left_pid, &left_status, 0) == -1)
	{
		if (errno != ECHILD && errno != EINTR)
			error_perror("sig_pipex", "left waitpid failed");
	}
	if (waitpid(right_pid, &right_status, 0) == -1)
	{
		if (errno == EINTR)
		{
			write(STDOUT_FILENO, "\n", 1);
			sig_set_signal(MAIN);
			return (130);
		}
		if (errno != ECHILD)
			error_perror("sig_pipex", "right waitpid failed");
		sig_set_signal(MAIN);
		return (0);
	}
	sig_set_signal(MAIN);
	return (sig_status(right_status));
}
