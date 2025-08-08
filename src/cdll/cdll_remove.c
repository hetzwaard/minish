/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdll_remove.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/09 00:06:18 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/09 00:06:18 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cdll_remove_node(t_cdll **head, t_cdll *node)
{
	if ((!head && !*head) || !node)
		return ;
	if (node->data)
		free(node->data);
	if (node == *head)
	{
		if ((*head)->next == *head)
		{
			free(*head);
			*head = NULL;
			return ;
		}
		*head = node->next;
	}
	node->next->prev = node->prev;
	node->prev->next = node->next;
	free(node);
}

void	cdll_clear(t_cdll **head)
{
	t_cdll	*current;
	t_cdll	*next;

	if (!head && !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		cdll_remove_node(head, current);
		if (*head == NULL)
			break ;
		current = next;
	}
	free(head);
}
