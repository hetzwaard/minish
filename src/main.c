/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 19:36:20 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/30 12:28:45 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signals;

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = NULL;
	shell = init_shell(shell, argc, argv, envp);
	while (1)
	{
		sig_setup();
		free_cmd_line(shell);
		shell->input = readline(prompt(shell));
		if (!shell->input)
			break ;
		if (shell->input[0])
			add_history(shell->input);
		init_input(shell);
		if (parser(shell->head, shell, NO_PARENTHESIS))
			continue ;
		shell->tree = create_tree(*shell->head, (*shell->head)->prev->prev);
		exec_tree(shell->tree, shell);
	}
	ft_printf("exit\n");
	exit_shell(shell);
	return (0);
}
