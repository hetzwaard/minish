/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_quote.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 09:34:00 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 09:34:15 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	error_quote(char *cmd, char *msg)
{
	ft_putstr_fd("minish: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (-1);
}
