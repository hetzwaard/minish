/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_redir.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 20:15:48 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/13 20:15:48 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_text(t_cdll *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (token->type == TOKEN_WORD || token->type == TOKEN_STRING
		|| token->type == TOKEN_LITTERAL)
		return (1);
	return (0);
}

int	is_redir(t_cdll *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	is_heredoc(t_cdll *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (token->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	is_redir_in(t_cdll *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (token->type == TOKEN_REDIR_IN)
		return (1);
	return (0);
}

int	is_redir_out(t_cdll *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (token->type == TOKEN_REDIR_OUT || token->type == TOKEN_APPEND)
		return (1);
	return (0);
}
