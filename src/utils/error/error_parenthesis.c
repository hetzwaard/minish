/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_parenthesis.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 21:08:01 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/13 21:08:01 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	error_parenthesis(void)
{
	ft_putstr_fd("minish: syntax error near unexpected token ", 2);
	ft_putstr_fd("`)'", 2);
	ft_printf("\n");
	return (-1);
}
