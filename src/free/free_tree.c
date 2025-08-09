/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_tree.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/09 02:56:40 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/09 02:56:53 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tree(t_tree *root)
{
	if (!root)
		return ;
	if (root->left)
		free_tree(root->left);
	if (root->right)
		free_tree(root->right);
	free(root);
	root = NULL;
}
