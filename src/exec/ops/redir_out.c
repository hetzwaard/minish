/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_out.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 07:00:30 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 10:31:53 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	redir_flag(t_cdll *node)
{
	if (((t_token *) node->data)->type == TOKEN_REDIR_OUT)
		return (O_TRUNC);
	else
		return (O_APPEND);
}

t_cdll	*next_redir_out(t_cdll *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	while (1)
	{
		node = node->next;
		token = (t_token *) node->data;
		if (token->type == TOKEN_REDIR_OUT || token->type == TOKEN_APPEND)
			return (node);
		if (!is_text(node))
			break ;
	}
	return (NULL);
}

int	redir_out_from_node(t_cdll *node, t_shell *shell, int flag)
{
	t_token	*token;
	char	*filename;
	int		fd;

	token = (t_token *) node->next->data;
	if (!token || token->priority != 6 || !token->start)
		return (error_shell("redir_from_node", "invalid arguments"));
	filename = exec_filename(node->next, shell);
	if (!filename)
		return (1);
	fd = open(filename, O_CREAT | O_WRONLY | flag, 0644);
	if (fd == -1)
		return (error_open(filename));
	free(filename);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), error_perror("redir_out", "dup2 failed"));
	close(fd);
	return (0);
}

int	redir_out(t_cdll *node, t_shell *shell)
{
	int		flag;

	if (!node || !shell)
		return (error_shell("redir_out", "invalid arguments"));
	flag = redir_flag(node);
	return (redir_out_from_node(node, shell, flag));
}
