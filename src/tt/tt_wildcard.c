/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tt_wildcard.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 07:18:42 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 07:33:07 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cdll	*tt_wildcard_insert_node(t_token *token, t_cdll *anchor)
{
	t_cdll	*new_node;

	new_node = cdll_create_node(token);
	if (!new_node)
	{
		free(token->start);
		free(token);
		error_shell("tt_wildcard_insert_nodes", "cdll_create_node failed");
		return (NULL);
	}
	new_node->next = anchor->next;
	new_node->prev = anchor;
	anchor->next->prev = new_node;
	anchor->next = new_node;
	return (new_node);
}

static void	tt_wildcard_set_token(t_token *token, char *matching_str)
{
	token->type = TOKEN_LITTERAL;
	token->start = ft_strdup(matching_str);
	token->end = NULL;
	token->space = 1;
	token->priority = 6;
	token->str_is_malloc = 1;
}

static void	tt_wildcard_insert_nodes(t_cdll *node, char **matching_array)
{
	t_cdll	*current;
	t_token	*token;
	size_t	i;

	current = node;
	i = 1;
	while (matching_array[i])
	{
		token = (t_token *) malloc(sizeof(t_token) + 1);
		if (!token)
		{
			error_shell("tt_wildcard_insert_nodes", "malloc failed");
			return ;
		}
		tt_wildcard_set_token(token, matching_array[i]);
		tt_wildcard_insert_node(token, current);
		current = current->next;
		i++;
	}
}

char	*tt_wildcard(char *arg, t_cdll *node, t_shell *shell)
{
	char	**file_array;
	char	**matching_array;
	char	*ret;
	char	pwd[PATH_MAX];
	int		mode;

	(void) shell;
	if (arg && arg[0] == '.')
		mode = W_HIDDEN;
	else
		mode = NO_HIDDEN;
	if (((t_token *) node->data)->type != TOKEN_WORD || !ft_strchr(arg, '*'))
		return (arg);
	file_array = tt_dirlist(getcwd(pwd, sizeof(pwd)), mode);
	if (!file_array)
		return (arg);
	matching_array = tt_filenames(arg, file_array);
	if (!matching_array)
		return (free_str_tab(file_array), arg);
	free_str_tab(file_array);
	tt_wildcard_insert_nodes(node, matching_array);
	ret = ft_strdup(matching_array[0]);
	free_str_tab(matching_array);
	return (free(arg), ret);
}
