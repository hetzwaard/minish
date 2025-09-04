/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paranthesis.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 08:28:15 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 08:33:14 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	parenthesis_del_str(t_cdll **head)
{
	t_cdll	*current;
	t_token	*tok;

	current = *head;
	while (1)
	{
		tok = (t_token *) current->data;
		if (tok->str_is_malloc)
		{
			free(tok->start);
			tok->start = NULL;
			tok->str_is_malloc = 0;
		}
		current = current->next;
		if (current == *head)
			break ;
	}
}

static int	parenthesis_subshell(t_cdll **head, t_shell *shell)
{
	t_tree	*tree;
	int		status;

	tree = create_tree(*head, (*head)->prev->prev);
	status = exec_tree(tree, shell);
	parenthesis_del_str(head);
	free_tree(tree);
	return (status);
}

int	parenthesis(t_tree *tree, t_shell *shell)
{
	int		status;
	pid_t	pid;
	t_cdll	**head;

	if (!tree || !shell)
		return (error_shell("parenthesis", "invalid arguments"), -1);
	pid = fork();
	if (pid == -1)
		return (error_perror("parenthesis", "fork failed"), -1);
	if (pid == 0)
	{
		head = lexer_tokenize(((t_token *) tree->list_node->data)->start);
		status = parenthesis_subshell(head, shell);
		cdll_clear(head);
		exit_shell(shell, status);
	}
	if (waitpid(pid, &status, 0) == -1)
		return (error_perror("parenthesis", "waitpid failed"), -1);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
