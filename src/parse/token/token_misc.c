/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_misc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 20:17:04 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 09:54:10 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_space(t_cdll *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (token->space)
		return (1);
	return (0);
}

int	is_filename(t_cdll *node)
{
	while (is_text(node) && !is_space(node->prev) && is_text(node->prev))
		node = node->prev;
	if (is_redir(node->prev))
		return (1);
	return (0);
}

int	is_and_or(t_cdll *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (token->type == TOKEN_AND || token->type == TOKEN_OR)
		return (1);
	return (0);
}

int	is_semicolon(t_cdll *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (token->type == TOKEN_SEMICOLON)
		return (1);
	return (0);
}
