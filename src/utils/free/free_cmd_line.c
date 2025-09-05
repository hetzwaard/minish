/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_cmd_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/09 02:57:13 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/09 02:57:22 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_cmd_line(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->stdin_backup)
		close(shell->stdin_backup);
	if (shell->stdout_backup)
		close(shell->stdout_backup);
	if (shell->input)
		free(shell->input);
	if (shell->input_cpy)
		free(shell->input_cpy);
	if (shell->head)
	{
		free_strings(shell);
		cdll_clear(shell->head);
	}
	if (shell->tree)
		free_tree(shell->tree);
	shell->input = NULL;
	shell->input_cpy = NULL;
	shell->head = NULL;
	shell->tree = NULL;
}
