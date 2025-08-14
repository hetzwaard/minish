/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_tree.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 05:40:44 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 10:32:16 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_logical_operator(t_tree *tree, t_shell *shell)
{
	if (tree->type == TREE_AND)
	{
		shell->exit_status = exec_tree(tree->left, shell);
		if (shell->exit_status == 0)
			shell->exit_status = exec_tree(tree->right, shell);
	}
	else if (tree->type == TREE_OR)
	{
		shell->exit_status = exec_tree(tree->left, shell);
		if (shell->exit_status != 0)
			shell->exit_status = exec_tree(tree->right, shell);
	}
	else if (tree->type == TREE_SEMICOLON)
	{
		if (tree->left)
			shell->exit_status = exec_tree(tree->left, shell);
		if (tree->right)
			shell->exit_status = exec_tree(tree->right, shell);
	}
	else
		shell->exit_status = error_shell("exec_tree",
				"invalid tree node type");
	return (shell->exit_status);
}

int	exec_tree(t_tree *tree_node, t_shell *shell)
{
	if (!tree_node)
		return (0);
	else if (tree_node->type == TREE_COMMAND)
		shell->exit_status = exec_leaf(tree_node->list_node, shell);
	else if (tree_node->type == TREE_PARENTHESIS)
		shell->exit_status = parenthesis(tree_node, shell);
	else if (tree_node->type == TREE_PIPE)
		shell->exit_status = pipex(tree_node, shell);
	else
		shell->exit_status = exec_logical_operator(tree_node, shell);
	return (shell->exit_status);
}
