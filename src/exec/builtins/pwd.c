/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 08:49:49 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 10:29:35 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	pwd_cmd(char **args, char **envp)
{
	char	current_dir[PATH_MAX];
	char	*pwd_env;

	(void)args;
	if (getcwd(current_dir, sizeof(current_dir)))
	{
		ft_printf("%s\n", current_dir);
		return (0);
	}
	pwd_env = get_env_value("PWD", envp);
	if (pwd_env)
	{
		ft_printf("%s\n", pwd_env);
		return (0);
	}
	return (error_shell("pwd", "getcwd failed"));
}
