/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_token.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/05 15:53:33 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:39:45 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

static int	is_meta_char(t_parsing *p, char *input)
{
	if (input[p->index] == '<' 
		|| input[p->index] == '>' 
		|| input[p->index] == '|')
		return (1);
	return (0);
}

static void	skip_meta_characters(t_parsing *p, char *input)
{
	if ((input[p->index] == '<' || input[p->index] == '>') 
				&& (input[p->index + 1] == input[p->index]))
	{
		p->token->len += 2;
		p->index += 2;
	}
	else
	{
		p->token->len += 1;
		p->index += 1;
	}
}

void get_token(t_parsing *p, char *input)
{
	p->token->start = p->index;
	p->token->len = 0;
	while (input[p->index]) 
	{
		check_quotes(input[p->index], &p->token->quote_flag);
		if (input[p->index] == ' ' && p->token->quote_flag == 0)
			break;
		if (is_meta_char(p, input) == 1 
			&& p->token->quote_flag == 0 
			&& p->token->len == 0)
		{
			skip_meta_characters(p, input);
			break ;
		}
		p->token->len++;
		p->index++;
	}
	skip_whitespaces(input, &p->index);
	p->token->type = get_token_type(input, p->token);
	p->token->end = p->index;
}
