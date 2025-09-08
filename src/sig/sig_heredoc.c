/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sig_heredoc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/08 13:51:44 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/09/08 13:52:32 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	sig_heredoc(pid_t pid)
{
	int	status;

	status = 0;
	sig_set_signal(PARENT);
	if (waitpid(pid, &status, 0) == -1)
	{
		sig_set_signal(MAIN);
		if (errno == EINTR)
			return (130);
		return (error_perror("sig_heredoc", "waitpid failed"));
	}
	sig_set_signal(MAIN);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status) && WEXITSTATUS(status) == 255)
		return (-1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
