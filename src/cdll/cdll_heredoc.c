/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdll_heredoc.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 07:38:31 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 07:39:17 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cdll	*cdll_next_heredoc(t_cdll *node)
{
	t_cdll	*current;

	current = node;
	while (!is_logical_operator(current) && !is_eof(current))
	{
		if (is_heredoc(current))
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_cdll	*cdll_next_cmd(t_cdll *node)
{
	t_cdll	*current;

	current = node;
	while (!is_tree_branch(current) && !is_eof(current))
	{
		if (is_redir(current))
			current = current->next;
		else if (is_text(current))
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_cdll	*cdll_next_redir(t_cdll *node)
{
	t_cdll	*current;

	current = node;
	while (!is_tree_branch(current) && !is_eof(current))
	{
		if (is_redir(current))
			return (current);
		current = current->next;
	}
	return (NULL);
}
