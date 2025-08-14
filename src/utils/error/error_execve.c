/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_execve.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 09:42:45 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 09:42:54 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	error_execve(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}
