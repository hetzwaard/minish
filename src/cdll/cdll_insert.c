/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdll_insert.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/09 00:02:28 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/09 00:02:28 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cdll	*cdll_add_front(t_cdll **head, void *data)
{
	t_cdll	*new;

	new = cdll_create_node(data);
	if (!new)
		return (NULL);
	if (!*head)
		*head = new;
	else
	{
		new->next = *head;
		new->prev = (*head)->prev;
		(*head)->prev->next = new;
		(*head)->prev = new;
		*head = new;
	}
	return (new);
}

t_cdll	*cdll_add_back(t_cdll **head, void *data)
{
	t_cdll	*new;

	new = cdll_create_node(data);
	if (!new)
		return (NULL);
	if (!*head)
		*head = new;
	else
	{
		new->next = *head;
		new->prev = (*head)->prev;
		(*head)->prev->next = new;
		(*head)->prev = new;
	}
	return (new);
}
