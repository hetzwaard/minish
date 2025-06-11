/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 18:17:55 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:44:35 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minish.h"

void error_and_exit(char *msg, t_minish *minish)
{
	(void)minish;
	//free_all(minish);
	perror(msg);
	exit(EXIT_FAILURE);
}