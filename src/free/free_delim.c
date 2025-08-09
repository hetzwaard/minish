/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_delim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/09 02:56:19 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/09 02:56:28 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_delim(t_delim *delim)
{
	if (!delim)
		return ;
	if (delim->str)
		free(delim->str);
	free(delim);
}
