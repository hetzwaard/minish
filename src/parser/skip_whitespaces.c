/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   skip_whitespaces.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/28 13:37:59 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:39:55 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

void skip_whitespaces(char *input, int *index)
{
	while (input[*index] && input[*index] == ' ')
		(*index)++;
}

