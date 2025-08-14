/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_filename.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 07:03:01 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 09:47:57 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_filename_ambiguous(char *arg, t_cdll *node)
{
	char	**file_array;
	char	**matching_array;
	char	pwd[PATH_MAX];
	int		mode;

	if (arg && arg[0] == '.')
		mode = W_HIDDEN;
	else
		mode = NO_HIDDEN;
	if (((t_token *) node->data)->type != TOKEN_WORD || !ft_strchr(arg, '*'))
		return (0);
	file_array = tt_dirlist(getcwd(pwd, sizeof(pwd)), mode);
	if (!file_array)
		return (0);
	matching_array = tt_filenames(arg, file_array);
	if (!matching_array)
		return (free_str_tab(file_array), 0);
	free_str_tab(file_array);
	if (get_env_count(matching_array) > 1)
	{
		error_shell(arg, "ambiguous redirect");
		return (free_str_tab(matching_array), 1);
	}
	free_str_tab(matching_array);
	return (0);
}

static char	*exec_filename_concat(char *filename, t_cdll *node, t_shell *shell)
{
	char	*next_arg;
	char	*temp;

	next_arg = tt_dollar((t_token *) node->data, shell);
	if (!next_arg)
		return (error_shell("add_arg", "malloc failed"), filename);
	temp = filename;
	filename = ft_strjoin(filename, next_arg);
	if (!filename)
		error_shell("add_arg", "ft_strjoin failed");
	free(temp);
	free(next_arg);
	return (filename);
}

char	*exec_filename(t_cdll *node, t_shell *shell)
{
	char	*filename;

	filename = tt_dollar((t_token *) node->data, shell);
	while (!is_space(node) && is_text(node->next))
	{
		filename = exec_filename_concat(filename, node->next, shell);
		if (!filename)
			return (NULL);
		node = node->next;
	}
	if (exec_filename_ambiguous(filename, node))
		return (free(filename), NULL);
	filename = tt_wildcard(filename, node, shell);
	return (filename);
}
