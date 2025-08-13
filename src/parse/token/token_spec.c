/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_spec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 21:00:53 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/13 21:00:53 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	parse_pipe(char **s)
{
	int	ret;

	ret = TOKEN_PIPE;
	if (*(*s + 1) == '|')
	{
		ret = TOKEN_OR;
		(*s)++;
	}
	(*s)++;
	return (ret);
}

int	parse_ampersand(char **s, char *es)
{
	int	ret;

	if (*(*s + 1) == '&')
	{
		ret = TOKEN_AND;
		(*s) += 2;
		return (ret);
	}
	ret = TOKEN_WORD;
	(*s)++;
	while (*s != es && !ft_strchr(WHITESPACES, **s) && !ft_strchr(SYMBOLS, **s))
		(*s)++;
	return (ret);
}

int	parse_semicolon(char **s)
{
	int	ret;

	ret = TOKEN_SEMICOLON;
	(*s)++;
	return (ret);
}

int	parse_double_quote(char **s, char *es)
{
	int	ret;

	(*s)++;
	while (*s != es && **s != '"')
		(*s)++;
	if (**s != '"')
	{
		ft_putstr_fd("minishell: syntax error unclosed double quote\n", 2);
		ret = TOKEN_ERROR;
	}
	else
	{
		ret = TOKEN_STRING;
		(*s)++;
	}
	return (ret);
}

int	parse_single_quote(char **s, char *es)
{
	int	ret;

	(*s)++;
	while (*s != es && **s != '\'')
		(*s)++;
	if (**s != '\'')
	{
		ft_putstr_fd("minishell: syntax error unclosed single quote\n", 2);
		ret = TOKEN_ERROR;
	}
	else
	{
		ret = TOKEN_LITTERAL;
		(*s)++;
	}
	return (ret);
}
