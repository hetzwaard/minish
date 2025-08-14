/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_open.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 07:01:37 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 07:01:52 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	error_open(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	perror(filename);
	free(filename);
	return (-1);
}
