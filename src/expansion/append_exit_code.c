/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   append_exit_code.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 13:18:23 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:43:29 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

int	append_exit_code(t_expansion *expan, int *i)
{
	char	*exit_code;
	char	*temp;

	exit_code = ft_itoa(expan->exit_code_copy);
	if (exit_code == NULL)
		return (-1);
	temp = ft_strjoin(expan->expanded_input, exit_code);
	if (temp == NULL)
	{
		free(exit_code);
		return (-1);
	}
	free(expan->expanded_input);
	expan->expanded_input = temp;
	(*i) += 1;
	return (0);
}