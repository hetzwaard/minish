/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 18:13:23 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:40:49 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

t_cmd_table *parse_input(t_parsing *p, char *input)
{
	while(input[p->index])
	{
		get_token(p, input);
		if (add_command(p, input) == -1)
				return (NULL);
		if (add_pipe(p) == -1)
				return (NULL);
		if (p->token->type == RE_APPEND || p->token->type == RE_IN
			|| p->token->type == RE_OUT || p->token->type == HERE_DOC)
		{
			if (add_redirect(p, input) == -1)
				return (NULL);
		}
	} 
	return (p->cmd_table);
}

int	parser(t_minish *minish)
{
	t_parsing	parsing;

	if (expand_input(minish) == -1)
	{
		minish->exit_code = ENOMEM;
		return (-1);
	}
	printf("expanded input %s", minish->input);
	if (init_parsing(&parsing) == -1)
	{
		minish->exit_code = ENOMEM;
		return (-1);
	}
	minish->cmd_table = parse_input(&parsing, minish->input);
	if (!minish->cmd_table) // ?
	{
		//free_parsing(parsing);
		ft_putstr_fd(parsing.parser_error, STDERR_FILENO);
		return (-1);
	}
	return(0);
}

//  char *test_input = "\'$PWD\'";
// 	char *expanded_input;

// 	expanded_input = expand_input(minish, test_input);
// 	printf("%s\n", expanded_input);