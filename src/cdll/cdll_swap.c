/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdll_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/09 00:10:00 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/09 00:10:00 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cdll_update_prev(t_cdll *head)
{
	t_cdll	*current;

	current = head;
	if (!head)
		return ;
	while (current->next != head)
	{
		current->next->prev = current;
		current = current->next;
	}
	current->next->prev = current;
}

static void	cdll_swap_non_adjacent(t_cdll *node1, t_cdll *node2)
{
	t_cdll	*temp_next;
	t_cdll	*temp_prev;

	temp_next = node1->next;
	temp_prev = node1->prev;
	node1->prev->next = node2;
	node1->next->prev = node2;
	node2->prev->next = node1;
	node2->next->prev = node1;
	node1->next = node2->next;
	node1->prev = node2->prev;
	node2->next = temp_next;
	node2->prev = temp_prev;
}

static void	cdll_swap_adjacent(t_cdll *node1, t_cdll *node2)
{
	if (node1->next == node2)
	{
		node1->next = node2->next;
		node1->prev->next = node2;
		node2->next->prev = node1;
		node2->prev = node1->prev;
		node2->next = node1;
		node1->prev = node2;
	}
	else
	{
		node2->prev->next = node1;
		node1->next->prev = node2;
		node2->next = node1->next;
		node1->prev = node2->prev;
		node2->prev = node1;
		node1->next = node2;
	}
}

int	cdll_swap_nodes(t_cdll **head, t_cdll *node1, t_cdll *node2)
{
	if ((!head && !*head) || !node1 || !node2 || (node1 == node2))
		return (-1);
	if (*head == node1)
		*head = node2;
	else if (*head == node2)
		*head = node1;
	if (node1->next == node2 && node2->next == node1)
	{
		node1->prev->next = node2;
		node2->next->prev = node1;
		node1->next = node2->next;
		node1->prev = node2;
		node2->next = node1;
		node2->prev = node1->prev;
	}
	else if (node1->next == node2 || node2->next == node1)
		cdll_swap_adjacent(node1, node2);
	else
		cdll_swap_non_adjacent(node1, node2);
	cdll_update_prev(*head);
	return (0);
}

void	cdll_move_node(t_cdll **src, t_cdll **dst, t_cdll *node)
{
	if (node == *src)
	{
		if ((*src)->next == *src)
			*src = NULL;
		else
			*src = node->next;
	}
	node->next->prev = node->prev;
	node->prev->next = node->next;
	if (!*dst)
	{
		*dst = node;
		node->next = node;
		node->prev = node;
	}
	else
	{
		node->next = *dst;
		node->prev = (*dst)->prev;
		(*dst)->prev->next = node;
		(*dst)->prev = node;
		*dst = node;
	}
}
