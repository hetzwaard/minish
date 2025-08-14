/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 20:36:30 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/13 20:36:30 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	print_token(t_token *token)
{
	if (token->type == TOKEN_PARENTHESIS)
		ft_putstr_fd("`)'", 2);
	else if (token->type == TOKEN_PIPE)
		ft_putstr_fd("`|'", 2);
	else if (token->type == TOKEN_AND)
		ft_putstr_fd("`&&'", 2);
	else if (token->type == TOKEN_OR)
		ft_putstr_fd("`||'", 2);
	else if (token->type == TOKEN_SEMICOLON)
		ft_putstr_fd("`;'", 2);
	else if (token->type == TOKEN_REDIR_OUT)
		ft_putstr_fd("`>'", 2);
	else if (token->type == TOKEN_APPEND)
		ft_putstr_fd("`>>'", 2);
	else if (token->type == TOKEN_REDIR_IN)
		ft_putstr_fd("`<'", 2);
	else if (token->type == TOKEN_HEREDOC)
		ft_putstr_fd("`<<'", 2);
	else if (token->type == TOKEN_EOF)
		ft_putstr_fd("`newline'", 2);
	else
		ft_putstr_fd(token->start, 2);
}

int	error_token(t_token *token)
{
	ft_putstr_fd("minish: syntax error near unexpected token ", 2);
	print_token(token);
	ft_printf("\n");
	return (258);
}
