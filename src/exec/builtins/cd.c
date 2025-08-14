/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 08:49:29 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 10:29:20 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*cd_get_pwd(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, sizeof(pwd)))
		return (error_shell("cd", "getcwd failed"), NULL);
	return (ft_strdup(pwd));
}

static void	cd_update_env(char *old, char ***envp, t_shell *shell, char *pwd)
{
	if (env_update("OLDPWD", '=', old, envp) == -1)
		error_shell("cd", "failed to create OLDPWD");
	if (env_update("PWD", '=', pwd, envp) == -1)
		error_shell("cd", "failed to create PWD");
	if (shell->pwd)
		free(shell->pwd);
	shell->pwd = cd_get_pwd();
}

static char	*cd_get_path(char *input, char **envp, char *home, char *old)
{
	if ((!input || *input == '\0') && !home)
		return (error_shell("cd", "HOME not set"), NULL);
	if (!input || *input == '\0')
		input = home;
	if (!ft_strncmp(input, "-", 1) && ft_strlen(input) == 1)
	{
		if (!old)
			return (error_shell("cd", "OLDPWD not set"), NULL);
		else
			return (ft_strdup(get_env_value("OLDPWD", envp)));
	}
	else
		return (ft_strdup(input));
}

int	cd_cmd(char **args, char ***envp, t_shell *shell)
{
	char	*new_pwd;
	char	*path;
	char	*old;

	if (!args || !envp || !args[0])
		return (error_shell("cd", "invalid arguments"));
	old = get_env_value("OLDPWD", *envp);
	path = args[1];
	new_pwd = cd_get_path(path, *envp, get_env_value("HOME", *envp), old);
	if (!new_pwd)
		return (-1);
	if (chdir(new_pwd) == -1)
		return (free(new_pwd), error_perror("cd", args[1]));
	free(new_pwd);
	new_pwd = cd_get_pwd();
	cd_update_env(shell->pwd, envp, shell, new_pwd);
	if (new_pwd)
		free(new_pwd);
	if (args[1] && args[1][0] == '-' && args[1][1] == '\0')
		ft_printf("%s\n", get_env_value("PWD", *envp));
	return (0);
}
