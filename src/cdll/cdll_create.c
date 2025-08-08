/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdll_create.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/09 00:00:22 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/09 00:00:22 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cdll	*cdll_create_node(void *data)
{
	t_cdll	*new;

	new = (t_cdll *) malloc(sizeof(t_cdll));
	if (!new)
		return (NULL);
	new->data = data;
	new->next = new;
	new->prev = new;
	return (new);
}
