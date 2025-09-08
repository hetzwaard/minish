/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_heredoc.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 06:04:16 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/09/08 13:26:36 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	heredoc_print_line(int fd, char *line, t_shell *shell, t_delim *lim)
{
	char	*temp;

	if (lim->is_litteral)
		temp = ft_strdup(line);
	else
		temp = tt_expand(line, shell);
	if (!temp)
		return ;
	ft_putstr_fd(temp, fd);
	free(temp);
	ft_putstr_fd("\n", fd);
}

static int	heredoc_file(t_delim *delim, t_shell *shell)
{
	int			fd;
	char		*line;
	static int	n_line = 0;

	fd = open(TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (error_perror("heredoc_file", "open failed"));
	while (++n_line)
	{
		line = readline(CLOVER "☘️  > " RESET);
		if (!line)
		{
			error_warning(delim->str, n_line);
			break ;
		}
		if (!ft_strncmp(line, delim->str, ft_strlen(line))
			&& ft_strlen(line) == ft_strlen(delim->str))
		{
			free(line);
			break ;
		}
		heredoc_print_line(fd, line, shell, delim);
		free(line);
	}
	return (free_delim(delim), close(fd), 0);
}

static t_delim	*heredoc_find_delimiter(t_cdll *node)
{
	t_delim	*lim;
	t_cdll	*current;
	char	*temp;

	lim = (t_delim *) malloc(sizeof(t_delim));
	if (!lim)
		return (error_shell("find_delimiter", "malloc failed"), NULL);
	ft_memset(lim, 0, sizeof(t_delim));
	current = node->next;
	lim->str = ft_strdup(((t_token *) current->data)->start);
	if (((t_token *) current->data)->type != TOKEN_WORD)
		lim->is_litteral = 1;
	if (!lim->str)
		return (error_shell("find_delimiter", "ft_strdup failed"), NULL);
	while (!((t_token *) current->data)->space && is_text(current->next))
	{
		if (((t_token *) current->data)->type != TOKEN_WORD
			|| ((t_token *) current->next->data)->type != TOKEN_WORD)
			lim->is_litteral = 1;
		temp = lim->str;
		lim->str = ft_strjoin(temp, ((t_token *) current->next->data)->start);
		free(temp);
		current = current->next;
	}
	return (lim);
}

static void	heredoc_child(t_cdll *node, t_shell *shell)
{
	t_cdll		*current;
	t_delim		*delimiter;

	sig_set_signal(HEREDOC);
	current = cdll_next_heredoc(node);
	while (1)
	{
		if (!current)
			break ;
		delimiter = heredoc_find_delimiter(current);
		if (!delimiter)
			exit(255);
		if (heredoc_file(delimiter, shell))
			exit(255);
		current = cdll_next_heredoc(current->next);
	}
	exit(0);
}

int	init_heredoc(t_cdll *node, t_shell *shell)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (error_perror("init_heredoc", "fork failed"));
	if (pid == 0)
		heredoc_child(node, shell);
	status = sig_heredoc(pid);
	return (status);
}
