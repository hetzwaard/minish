/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_perror.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 20:42:02 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/13 20:42:02 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	error_perror(char *cmd, char *msg)
{
	ft_putstr_fd("minish: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	perror(msg);
	return (-1);
}
