/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 18:40:39 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:44:04 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

static bool	is_isolated(char *original_input, char quote_flag, int i)
{
	if (quote_flag == '\"' 
		&& (original_input[i + 1] == ' '
			|| original_input[i + 1] == '\0'
			|| original_input[i + 1] == '\"'))
		return(true);
	else if (original_input[i + 1] == ' ' 
			|| original_input[i + 1] == '\0')
		return (true);
	return (false);
}

static bool	is_exit_code(char *original_input, char quote_flag, int i)
{
	if (quote_flag != '\'' && original_input[i + 1] == '?')
		return (true);
	return (false);
}

int	handle_expansion(t_expansion *expan, char *input, int *i)
{
	if (is_isolated(input, expan->quote_flag, *i))
	{
		if (append_char(expan, input[*i]) == -1)
			return (-1);
	}
	else if (is_exit_code(input, expan->quote_flag, *i))
	{
		if (append_exit_code(expan, i) == -1)
			return (-1);
	}
	else if (expan->quote_flag == '\'')
	{
		if (append_char(expan, input[*i]) == -1)
			return (-1);
	}
	else if (append_variable(expan, input, i) == -1)
	{
		return (-1);
	}
	return (0);
}

static void init_expansion(t_minish *minish, t_expansion *expan)
{
	expan->expanded_input = NULL;
	expan->var_expanded = NULL;
	expan->var_name = NULL;
	expan->quote_flag = 0;
	expan->var_name_len = 0;
	expan->envp_copy = minish->envp;
	expan->exit_code_copy = minish->exit_code;
}

int expand_input(t_minish *minish)
{
	t_expansion	expan;
	int	i;

	i = 0;
	init_expansion(minish, &expan);
	while(minish->input[i])
	{
		check_quotes(minish->input[i], &expan.quote_flag);
		if (minish->input[i] == '$')
		{
			if (handle_expansion(&expan, minish->input, &i) == -1)
			{
				minish->exit_code = ENOMEM;
				return (free_expansion(&expan), -1);
			}
		}
		else if (append_char(&expan, minish->input[i]) == -1)
		{
			minish->exit_code = ENOMEM;
			return (free_expansion(&expan), -1);
		}
		i++;
	}
	free(minish->input);
	minish->input = expan.expanded_input;
	return (0);
}
