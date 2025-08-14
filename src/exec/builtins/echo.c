/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 08:49:35 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 10:29:24 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	echo_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	i++;
	if (str[i] != 'n')
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	echo_cmd(char **args, char **envp)
{
	int		newline;
	int		i;

	(void)envp;
	if (args[1] == NULL)
		return (ft_putchar_fd('\n', 1), 0);
	newline = 0;
	i = 1;
	while (echo_n(args[i]) == 0)
	{
		newline = 1;
		i++;
		if (args[i] == NULL)
			break ;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
