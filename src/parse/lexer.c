/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 20:48:43 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/09/05 20:52:57 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	lexer_finalize_tokens(t_cdll **head)
{
	t_cdll	*current;
	t_token	*token;

	if (!head || !*head)
		return ;
	current = *head;
	while (1)
	{
		token = (t_token *) current->data;
		if (token->type == TOKEN_PARENTHESIS || token->type == TOKEN_STRING
			|| token->type == TOKEN_LITTERAL)
		{
			token->start++;
			token->end--;
			*token->end = '\0';
		}
		else if (token->type == TOKEN_WORD)
			*token->end = '\0';
		token->end = NULL;
		current = current->next;
		if (current == *head)
			break ;
	}
}

static void	lexer_set_priorities(t_cdll **head)
{
	t_cdll	*current;
	t_token	*token;

	if (!head || !*head)
		return ;
	current = *head;
	while (1)
	{
		token = (t_token *) current->data;
		if (token->type >= TOKEN_STRING && token->type <= TOKEN_LITTERAL)
			token->priority = 6;
		else if (token->type == TOKEN_PIPE)
			token->priority = 1;
		else if (token->type == TOKEN_AND || token->type == TOKEN_OR
			||token->type == TOKEN_SEMICOLON)
			token->priority = 0;
		else if (token->type == TOKEN_PARENTHESIS)
			token->priority = 2;
		else
			token->priority = 10;
		current = current->next;
		if (current == *head)
			break ;
	}
}

static void	lexer_set_token_fields(t_token *token, int type,
	char *start, char *end)
{
	token->type = type;
	token->start = start;
	token->end = end;
	token->space = 0;
	token->str_is_malloc = 0;
	if (ft_strchr(WHITESPACES, *end))
		token->space = 1;
}

static int	lexer_fill_list(char *input, t_cdll **head)
{
	t_token	*token;
	char	*str;
	char	*start;
	char	*end;
	int		type;

	str = input;
	type = NOTHING;
	while (type != TOKEN_EOF)
	{
		type = parse_token(&str, input + ft_strlen(input), &start, &end);
		if (type == TOKEN_ERROR)
			return (-1);
		token = malloc(sizeof(*token));
		if (!token)
			return (-1);
		lexer_set_token_fields(token, type, start, end);
		cdll_add_back(head, token);
	}
	return (0);
}

t_cdll	**lexer_tokenize(char *input)
{
	t_cdll	**head;

	if (!input)
		return (NULL);
	head = ft_calloc(1, sizeof(*head));
	if (!head)
		return (NULL);
	if (lexer_fill_list(input, head) == -1)
		return (cdll_clear(head), NULL);
	lexer_set_priorities(head);
	lexer_finalize_tokens(head);
	return (head);
}
