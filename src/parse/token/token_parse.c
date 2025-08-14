/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_parse.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 20:56:16 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 09:53:59 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	parse_parenthesis(char **s, char *es)
{
	int		depth;
	char	*str;

	str = "minishell: syntax error near unexpected token ";
	if (**s == ')')
		return (ft_putstr_fd(str, 2), ft_putstr_fd("`)'\n", 2), TOKEN_ERROR);
	(*s)++;
	depth = 0;
	while (1)
	{
		if (*s == es)
			return (ft_putstr_fd(str, 2), ft_putstr_fd("`('\n", 2),
				TOKEN_ERROR);
		else if (**s == '(')
			depth++;
		else if (**s == ')')
		{
			if (depth == 0)
				break ;
			depth--;
		}
		(*s)++;
	}
	(*s)++;
	return (TOKEN_PARENTHESIS);
}

static int	parse_angle_bracket(char **s)
{
	int	ret;

	if (**s == '<')
	{
		ret = TOKEN_REDIR_IN;
		if (*(*s + 1) == '<')
		{
			ret = TOKEN_HEREDOC;
			(*s)++;
		}
	}
	else
	{
		ret = TOKEN_REDIR_OUT;
		if (*(*s + 1) == '>')
		{
			ret = TOKEN_APPEND;
			(*s)++;
		}
	}
	(*s)++;
	return (ret);
}

static int	parse_word(char **s, char *es)
{
	int	ret;

	ret = TOKEN_WORD;
	while (*s != es && !ft_strchr(WHITESPACES, **s) && !ft_strchr(SYMBOLS, **s))
		(*s)++;
	return (ret);
}

static int	parse_symbol(char **s, char *es)
{
	int	ret;

	ret = 0;
	if (**s == '>' || **s == '<')
		ret = parse_angle_bracket(s);
	else if (**s == '(' || **s == ')')
		ret = parse_parenthesis(s, es);
	else if (**s == ';')
		ret = parse_semicolon(s);
	else if (**s == '|')
		ret = parse_pipe(s);
	else if (**s == '&')
		ret = parse_ampersand(s, es);
	else if (**s == '"')
		ret = parse_double_quote(s, es);
	else if (**s == '\'')
		ret = parse_single_quote(s, es);
	return (ret);
}

int	parse_token(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACES, *s))
		s++;
	if (q)
		*q = s;
	if (s >= es)
		ret = TOKEN_EOF;
	else if (ft_strchr(SYMBOLS, *s))
		ret = parse_symbol(&s, es);
	else
		ret = parse_word(&s, es);
	if (eq)
		*eq = s;
	while (s < es && ft_strchr(WHITESPACES, *s))
		s++;
	*ps = s;
	return (ret);
}
