/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdll_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/09 00:24:34 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/09 00:24:34 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cdll_get_node_index(t_cdll *head, t_cdll *node)
{
	t_cdll	*current;
	int		position;

	if (!head || !node)
		return (-1);
	current = head;
	position = 0;
	while (current != node)
	{
		position++;
		current = current->next;
		if (current == head)
			return (-1);
	}
	return (position);
}

t_cdll	*cdll_get_node_at(t_cdll *head, int position)
{
	t_cdll	*current;
	int		i;

	if (!head)
		return (NULL);
	current = head;
	i = 0;
	while (i < position)
	{
		current = current->next;
		i++;
	}
	return (current);
}

int	cdll_get_node_count(t_cdll *head)
{
	t_cdll	*current;
	int		count;

	count = 0;
	if (head)
	{
		current = head;
		while (current->next != head)
		{
			count++;
			current = current->next;
		}
		count++;
	}
	return (count);
}
