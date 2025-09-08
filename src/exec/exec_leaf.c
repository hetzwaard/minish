/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_leaf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 05:54:25 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/09/08 13:04:18 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exec_restore_std(int stdin, int stdout)
{
	close(STDIN_FILENO);
	if (dup2(stdin, STDIN_FILENO) == -1)
		error_perror("redir_out", "dup2 failed");
	close(stdin);
	close(STDOUT_FILENO);
	if (dup2(stdout, STDOUT_FILENO) == -1)
		error_perror("redir_out", "dup2 failed");
	close(stdout);
}

static int	exec_redir(t_cdll *node, t_shell *shell)
{
	t_cdll	*current;
	int		redir_status;

	current = cdll_next_redir(node);
	while (current)
	{
		redir_status = 0;
		if (((t_token *)current->data)->type == TOKEN_HEREDOC)
			redir_status = redir_heredoc();
		else if (((t_token *)current->data)->type == TOKEN_REDIR_IN)
			redir_status = redir_in(current, shell);
		else if (is_redir_out(current))
			redir_status = redir_out(current, shell);
		if (redir_status != 0)
			return (1);
		current = cdll_next_redir(current->next);
	}
	return (0);
}

static int	exec_save_std(t_shell *shell)
{
	shell->stdin_backup = dup(STDIN_FILENO);
	if (shell->stdin_backup == -1)
		return (error_perror("exec_save_std", "dup failed"));
	shell->stdout_backup = dup(STDOUT_FILENO);
	if (shell->stdout_backup == -1)
		return (close(shell->stdin_backup), error_perror("exec_save_std",
				"dup failed"));
	return (0);
}

int	exec_leaf(t_cdll *node, t_shell *shell)
{
	int	status;
	int	hd_status;

	if (exec_save_std(shell) == -1)
		return (-1);
	if (!shell->in_pipe)
	{
		hd_status = init_heredoc(node, shell);
		if (hd_status != 0)
		{
			close(shell->stdin_backup);
			close(shell->stdout_backup);
			return (hd_status);
		}
	}
	if (exec_redir(node, shell))
		return (1);
	status = exec_cmd(cdll_next_cmd(node), shell);
	exec_restore_std(shell->stdin_backup, shell->stdout_backup);
	return (status);
}
