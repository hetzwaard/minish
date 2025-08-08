/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_shell.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 22:03:07 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/08 22:03:07 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_delim(t_delim *delim)
{
	if (!delim)
		return ;
	if (delim->str)
		free(delim->str);
	free(delim);
}

void	free_tree(t_tree *root)
{
	if (!root)
		return ;
	if (root->left)
		free_tree(root->left);
	if (root->right)
		free_tree(root->right);
	free(root);
	root = NULL;
}

void	free_strings(t_shell *shell)
{
	t_cdll	*current;
	t_token	*token;

	current = *shell->head;
	while (1)
	{
		token = (t_token *) current->data;
		if (token->str_is_malloc)
		{
			free(token->start);
			token->start = NULL;
			token->str_is_malloc = 0;
		}
		current = current->next;
		if (current == *shell->head)
			break ;
	}
}

void	free_cmd_line(t_shell *shell)
{
	if (shell->stdin_backup)
		close(shell->stdin_backup);
	if (shell->stdout_backup)
		close(shell->stdout_backup);
	if (!shell)
		return ;
	if (shell->input)
		free(shell->input);
	if (shell->input_cpy)
		free(shell->input_cpy);
	if (shell->head)
	{
		free_strings(shell);
		cdll_clear(shell->head);
	}
	if (shell->tree)
		free_tree(shell->tree);
	shell->input = NULL;
	shell->input_cpy = NULL;
	shell->head = NULL;
	shell->tree = NULL;
}

void	free_shell(t_shell *shell)
{
	rl_clear_history();
	if (!shell)
		return ;
	if (shell->envp)
		ft_free_arr(shell->envp);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->home)
		free(shell->home);
	free_cmd_line(shell);
	shell->envp = NULL;
	shell->pwd = NULL;
	shell->home = NULL;
	free(shell);
	shell = NULL;
}
