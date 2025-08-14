/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_args.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 09:45:16 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 09:50:03 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*exec_args_concat(char *arg, t_cdll *node, t_shell *shell)
{
	char	*next_arg;
	char	*temp;

	next_arg = tt_dollar((t_token *) node->data, shell);
	if (!next_arg)
		return (error_shell("add_arg", "malloc failed"), NULL);
	temp = arg;
	arg = ft_strjoin(arg, next_arg);
	if (!arg)
		error_shell("add_arg", "malloc failed");
	free(temp);
	free(next_arg);
	return (arg);
}

static char	**exec_args_expand(char **args, char *arg, int *i)
{
	args = realloc_str_arr(args, *i + 2);
	args[*i] = arg;
	(*i)++;
	if (!args)
		error_shell("exec_args_expand", "malloc failed");
	else
		args[*i] = NULL;
	return (args);
}

static t_cdll	*exec_args_next(t_cdll *node)
{
	t_cdll	*find;

	while (!is_tree_branch(node) && !is_eof(node))
	{
		if (is_text(node))
		{
			if (!is_redir(node->prev))
			{
				if (is_space(node->prev) || !is_text(node->prev))
					return (node);
				find = node->prev;
				while (is_text(find) && !is_space(find))
					find = find->prev;
				if (!is_redir(find))
				{
					if (is_redir(find->prev))
						return (node);
				}
			}
		}
		node = node->next;
	}
	return (NULL);
}

char	**exec_args(t_cdll *node, t_shell *shell)
{
	char	*arg;
	char	**args;
	int		i;

	args = realloc_str_arr(NULL, 1);
	node = exec_args_next(node);
	i = 0;
	while (node)
	{
		arg = tt_dollar((t_token *) node->data, shell);
		while (!is_space(node) && is_text(node->next))
		{
			arg = exec_args_concat(arg, node->next, shell);
			if (!arg)
				return (NULL);
			if (!is_space(node->next) && is_text(node->next->next))
				node = node->next;
			else
				break ;
		}
		arg = tt_wildcard(arg, node, shell);
		args = exec_args_expand(args, arg, &i);
		node = exec_args_next(node->next);
	}
	return (args);
}
