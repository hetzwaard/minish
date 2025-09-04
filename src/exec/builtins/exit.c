/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 08:49:42 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 10:32:09 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	exit_argslen(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

static void	exit_perform(char **args, t_shell *shell, int status)
{
	free_str_tab(args);
	exit_shell(shell, status);
}

void	exit_cmd(char **args, char **envp, t_shell *shell)
{
	long	exit_status;
	char	*endptr;

	(void)envp;
	ft_putstr_fd("exit\n", 1);
	if (!args[1])
		exit_perform(args, shell, 0);
	exit_status = ft_strtol(args[1], &endptr, 10);
	if (*endptr != '\0' || errno == ERANGE)
	{
		error_exit(args[1]);
		exit_perform(args, shell, 2);
	}
	if (exit_argslen(args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	exit_perform(args, shell, (exit_status) % 256);
}
