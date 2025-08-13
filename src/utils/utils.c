/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 22:26:46 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/08 22:26:46 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_shell(t_shell *shell)
{
	rl_clear_history();
	unlink(TEMP_FILE);
	free_shell(shell);
}
