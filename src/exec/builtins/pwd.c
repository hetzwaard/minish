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

	(void)args;
	(void)envp;
	if (!getcwd(current_dir, sizeof(current_dir)))
		return (error_shell("pwd", "getcwd failed"));
	else
		ft_printf("%s\n", current_dir);
	return (0);
}
