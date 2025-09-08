/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 06:58:49 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/09/08 13:05:16 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	redir_heredoc(void)
{
	int	fd;

	fd = open(TEMP_FILE, O_RDONLY);
	if (fd == -1)
		return (error_perror("redir_heredoc", "open failed"));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), error_perror("redir_heredoc", "dup2 failed"));
	close(fd);
	return (0);
}
