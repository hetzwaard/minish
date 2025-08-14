/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 08:52:25 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 08:52:36 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	error_exit(char *arg)
{
	ft_putstr_fd("minish: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}
