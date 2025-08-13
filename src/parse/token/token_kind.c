/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_kind.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 20:10:37 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/13 20:10:37 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_logical_operator(t_cdll *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (token->type == TOKEN_AND || token->type == TOKEN_OR
		|| token->type == TOKEN_SEMICOLON)
		return (1);
	return (0);
}

int	is_parenthesis(t_cdll *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (token->type == TOKEN_PARENTHESIS)
		return (1);
	return (0);
}

int	is_eof(t_cdll *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (token->type == TOKEN_EOF)
		return (1);
	return (0);
}

int	is_pipe(t_cdll *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (token->type == TOKEN_PIPE)
		return (1);
	return (0);
}

int	is_tree_branch(t_cdll *node)
{
	if (!node)
		return (0);
	if (is_logical_operator(node) || is_pipe(node) || is_parenthesis(node))
		return (1);
	return (0);
}
