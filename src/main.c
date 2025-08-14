/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 19:36:20 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 10:21:22 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signals;

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	shell = NULL;
	shell = init_shell(shell, ac, av, envp);
	while (g_signals != EOF)
	{
		init_signals();
		free_cmd_line(shell);
		shell->input = readline(CLOVER "🍀 MINISH > " RESET);
		if (!shell->input)
			break ;
		if (shell->input && shell->input[0] == '\n' && shell->input[0] != '\0')
			add_history(shell->input);
		if (!shell->input[0] || shell->input[0] == '\n')
			continue ;
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
