/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 08:33:04 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/24 12:28:22 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	pipex_write(int fd[], t_tree *tree, t_shell *shell)
{
	int	status;

	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		free_shell(shell);
		error_perror("pipex_write", "dup2 failed");
		exit(42);
	}
	close(fd[1]);
	status = exec_tree(tree->left, shell);
	free_shell(shell);
	exit(status);
}

static int	pipex_read(int fd[], t_tree *tree, t_shell *shell)
{
	int	status;

	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		free_shell(shell);
		error_perror("pipex_read", "dup2 failed");
		exit(42);
	}
	close(fd[0]);
	status = exec_tree(tree->right, shell);
	free_shell(shell);
	exit(status);
}

static int	pipex_heredoc(t_tree *tree, t_shell *shell)
{
	t_tree	*cuurent;

	shell->in_pipe = 1;
	cuurent = tree->left;
	if (!cuurent)
		return (1);
	while (cuurent->type != TREE_COMMAND && cuurent->type != TREE_PARENTHESIS)
	{
		cuurent = cuurent->left;
		if (!cuurent)
			return (1);
	}
	init_heredoc(cuurent->list_node, shell);
	return (0);
}

static int	pipex_close(int fd[2], int left_pid, int right_pid, t_shell *shell)
{
	int		left_status;
	int		right_status;

	shell->in_pipe = 0;
	close(fd[1]);
	close(fd[0]);
	if (waitpid(left_pid, &left_status, 0) == -1)
	{
		if (errno != ECHILD)
			error_perror("pipex_close", "left waitpid failed");
	}
	if (waitpid(right_pid, &right_status, 0) == -1)
	{
		if (errno != ECHILD)
			error_perror("pipex_close", "right waitpid failed");
		return (0);
	}
	if (WIFSIGNALED(right_status))
		return (128 + WTERMSIG(right_status));
	if (WIFEXITED(right_status))
		return (WEXITSTATUS(right_status));
	return (1);
}

int	pipex(t_tree *tree, t_shell *shell)
{
	int		fd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (!tree || !shell || !tree->left || !tree->right)
		return (error_shell("pipex", "invalid arguments"));
	if (!shell->in_pipe)
		pipex_heredoc(tree, shell);
	if (pipe(fd) == -1)
		return (error_perror("pipex", "pipe failed"));
	left_pid = fork();
	if (left_pid == -1)
		return (close(fd[0]), close(fd[1]),
			error_perror("pipex", "fork failed"));
	if (left_pid == 0)
		pipex_write(fd, tree, shell);
	right_pid = fork();
	if (right_pid == -1)
		return (close(fd[0]), close(fd[1]),
			error_perror("pipex", "fork failed"));
	if (right_pid == 0)
		pipex_read(fd, tree, shell);
	return (pipex_close(fd, left_pid, right_pid, shell));
}
