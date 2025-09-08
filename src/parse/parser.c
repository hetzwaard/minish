/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 23:55:21 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/09/08 08:55:51 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static int	append_input(t_shell *shell, t_cdll *node)
// {
// 	char	*line;
// 	char	*join;

// 	if (!shell || !shell->input_cpy || !node)
// 		return (error_shell("append_input", "invalid arguments"));
// 	line = readline(RED "> " RESET);
// 	if (!line || !line[0] || line[0] == '\n')
// 	{
// 		free(line);
// 		return (append_input(shell, node));
// 	}
// 	join = ft_strjoin(shell->input_cpy, line);
// 	if (!join)
// 		return (error_perror("append_input", "malloc failed"));
// 	free_cmd_line(shell);
// 	shell->input = join;
// 	add_history(shell->input);
// 	shell->input_cpy = ft_strdup(shell->input);
// 	if (!shell->input_cpy)
// 		return (error_perror("append_input", "ft_strdup failed"));
// 	shell->head = lexer_tokenize(shell->input);
// 	if (!shell->head)
// 		return (-1);
// 	free(line);
// 	return (parser(shell->head, shell, NO_PARENTHESIS));
// }

static int	validate_parenthesis(t_shell *shell, t_cdll *node)
{
	t_cdll	**head;
	char	*line;
	int		result;

	line = ft_strdup(((t_token *) node->data)->start);
	if (!line)
		return (error_perror("check_parenthesis", "ft_strdup failed"));
	head = lexer_tokenize(line);
	if (!head)
	{
		free(line);
		return (error_shell("check_parenthesis", "lexer_tokenize failed"));
	}
	if (is_eof(*head))
	{
		free(head);
		free(line);
		return (error_token((t_token *) node->data));
	}
	result = parser(head, shell, IN_PARENTHESIS);
	cdll_clear(head);
	free(line);
	return (result);
}

static int	validate_last_token(t_cdll *node, int state)
{
	if (is_redir(node->prev))
		return (error_token((t_token *) node->data));
	if (is_and_or(node->prev) || is_pipe(node->prev))
	{
		if (state == IN_PARENTHESIS)
			return (error_parenthesis());
		return (error_token(node->data));
	}
	return (0);
}

int	validate_nodes(t_cdll *current, t_shell *shell, int state)
{
	while (1)
	{
		if (is_logical_operator(current) || is_pipe(current))
			if (!is_text(current->prev) && !is_parenthesis(current->prev))
				return (error_token((t_token *) current->data));
		if (is_redir(current))
			if (is_redir(current->prev))
				return (error_token((t_token *) current->data));
		if (is_parenthesis(current))
		{
			if (!is_eof(current->prev) && !is_logical_operator(current->prev)
				&& !is_pipe(current->prev))
				return (error_token((t_token *) current->data));
			if (validate_parenthesis(shell, current))
				return (2);
		}
		current = current->next;
		if (is_eof(current))
			return (validate_last_token(current, state));
	}
}

int	parser(t_cdll **head, t_shell *shell, int state)
{
	int	status;

	if (!head || !*head)
		return (shell->exit_status = 2);
	status = validate_nodes(*head, shell, state);
	if (status != 0)
		shell->exit_status = 2;
	return (status);
}
