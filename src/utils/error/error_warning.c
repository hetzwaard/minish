/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_warning.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 06:14:29 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 06:14:39 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	error_warning(char *delimiter, int n_line)
{
	ft_putstr_fd("minishell: warning : here-document at line ", 2);
	ft_putnbr_fd(n_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
