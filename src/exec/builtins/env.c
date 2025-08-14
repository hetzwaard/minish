/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 08:49:38 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 10:29:26 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	env_cmd(char **args, char **envp)
{
	int	i;

	(void)args;
	if (!envp)
		return (error_shell("env_cmd", "invalid arguments"));
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strchr(envp[i], '='))
		{
			ft_putstr_fd(envp[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (0);
}
