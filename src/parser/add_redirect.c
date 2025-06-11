/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_redirect.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 15:57:41 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/11 01:53:35 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

static char	*get_file_name(t_token token, char *input)
{
	char	*file_name;
	// int		len;

	// len = token.end - token.start;
	file_name = ft_substr(input, token.start, token.len);
	if (!file_name)
		return (NULL);
	return (file_name);
}

static int handle_file_type(t_parsing *p, char *input)
{
	char	*file_name;

	file_name = get_file_name(*p->token, input);
	purge_quotes(p, &file_name);
	if (!file_name)
	{
		p->parser_error = "malloc error:";
		return (-1);
	}
	if (p->previous_token->type == HERE_DOC)
		handle_heredoc(p, file_name);
	if (open_file(p, file_name) == -1)
		return (-1);
	return (0);
}

static t_token	*copy_token_data(t_token *token)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = token->type;
	new_token->len = token->len;
	new_token->end = token->end;
	new_token->start = token->start;
	new_token->quote_flag = token->quote_flag;
	return (new_token);
}

int add_redirect(t_parsing *p, char *input)
{
	p->previous_token = copy_token_data(p->token);
	if (!p->previous_token)
	{
		p->parser_error = "malloc failure: ";
		return (-1);
	}
	get_token(p, input);
	if (p->token->type != WORD)
	{
		p->parser_error = ft_substr(input, \
						p->token->start, p->token->len);
								 // malloc protect.
		return (-1);
	}
	if (handle_file_type(p, input) == -1)
		return(-1);
	return (0);
}