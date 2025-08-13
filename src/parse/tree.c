/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 21:03:05 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/13 21:03:05 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	tree_node_type(t_token *token)
{
	if (token->type == TOKEN_PIPE)
		return (TREE_PIPE);
	else if (token->type == TOKEN_AND)
		return (TREE_AND);
	else if (token->type == TOKEN_OR)
		return (TREE_OR);
	else if (token->type == TOKEN_SEMICOLON)
		return (TREE_SEMICOLON);
	else if (token->type == TOKEN_PARENTHESIS)
		return (TREE_PARENTHESIS);
	else
		return (TREE_COMMAND);
}

static t_tree	*tree_create_node(t_cdll *list_node)
{
	t_tree	*tree_node;

	tree_node = (t_tree *) malloc(sizeof(t_tree));
	if (!tree_node)
		return (error_shell("tree_create_node", "malloc failed"), NULL);
	ft_memset(tree_node, 0, sizeof(t_tree));
	tree_node->list_node = list_node;
	tree_node->type = tree_node_type((t_token *) list_node->data);
	return (tree_node);
}

static t_cdll	*tree_find_lowest_priority(t_cdll *left, t_cdll *right)
{
	t_cdll	*current;
	t_cdll	*lowest;
	t_token	*token;
	t_token	*lowest_token;

	if (!left || !right)
		return (error_shell("tree_find_lowest_priority",
				"invalid arguments"), NULL);
	current = right;
	lowest = left;
	while (1)
	{
		lowest_token = (t_token *) lowest->data;
		token = (t_token *) current->data;
		if (is_tree_branch(current) && token->priority < lowest_token->priority)
			lowest = current;
		if (current == left)
			break ;
		current = current->prev;
	}
	return (lowest);
}

t_tree	*tree_create(t_cdll *left, t_cdll *right)
{
	t_tree	*tree_node;
	t_cdll	*lowest;

	if (!left || !right)
		return (error_shell("create tree", "invalid arguments"), NULL);
	lowest = tree_find_lowest_priority(left, right);
	tree_node = tree_create_node(lowest);
	if (!tree_node)
		return (NULL);
	if (is_tree_branch(lowest))
	{
		if (lowest != left)
			tree_node->left = tree_create(left, lowest->prev);
		if (lowest != right)
			tree_node->right = tree_create(lowest->next, right);
	}
	return (tree_node);
}
