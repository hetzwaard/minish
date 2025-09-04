/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_shell.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 22:03:07 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/09 02:57:26 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->envp)
		ft_free_arr(shell->envp);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->home)
		free(shell->home);
	free_cmd_line(shell);
	shell->envp = NULL;
	shell->pwd = NULL;
	shell->home = NULL;
	free(shell);
}

void	exit_shell(t_shell *shell, int status)
{
	rl_clear_history();
	unlink(TEMP_FILE);
	free_shell(shell);
	exit (status);
}
