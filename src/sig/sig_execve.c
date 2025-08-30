/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sig_execve.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/30 12:55:00 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/30 12:55:00 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	sig_execve(pid_t pid, char *ctx)
{
	int	status;

	status = 0;
	sig_set_signal(PARENT);
	if (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
		{
			write(STDOUT_FILENO, "\n", 1);
			sig_set_signal(MAIN);
			return (130);
		}
		sig_set_signal(MAIN);
		return (error_perror(ctx, "waitpid failed"), status);
	}
	sig_set_signal(MAIN);
	return (sig_status(status));
}
