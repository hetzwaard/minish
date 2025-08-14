/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_in.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 06:59:17 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 09:49:37 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	redir_in_from_node(t_cdll *node, t_shell *shell)
{
	t_token	*token;
	char	*filename;
	int		fd;

	token = (t_token *) node->next->data;
	if (!token || token->priority != 6 || !token->start)
		return (error_shell("redir_in", "invalid arguments"));
	filename = exec_filename(node->next, shell);
	if (!filename)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (error_open(filename));
	free(filename);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), error_perror("redir_in", "dup2 failed"));
	close(fd);
	return (0);
}

int	redir_in(t_cdll *node, t_shell *shell)
{
	if (!node || !shell)
		return (error_shell("redir_in", "invalid arguments"));
	return (redir_in_from_node(node, shell));
}
