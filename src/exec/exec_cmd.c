/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 08:44:27 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/09/27 10:53:28 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	(*exec_cmd_soft(char *cmd))(char **args, char **envp)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", 4) && len == 4)
		return (echo_cmd);
	else if (!ft_strncmp(cmd, "env", 3) && len == 3)
		return (env_cmd);
	else if (!ft_strncmp(cmd, "pwd", 3) && len == 3)
		return (pwd_cmd);
	return (NULL);
}

static int	(*exec_cmd_hard(char *cmd))(char **args, char ***envp)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "export", 6) && len == 6)
		return (export_cmd);
	else if (!ft_strncmp(cmd, "unset", 5) && len == 5)
		return (unset_cmd);
	return (NULL);
}

static int	exec_cmd_func(char **args, char ***envp, t_shell *shell)
{
	int	status;
	int	(*hard_built_func)(char **, char ***);
	int	(*soft_built_func)(char **, char **);

	hard_built_func = exec_cmd_hard(args[0]);
	soft_built_func = exec_cmd_soft(args[0]);
	if (hard_built_func)
		status = hard_built_func(args, envp);
	else if (soft_built_func)
		status = soft_built_func(args, *envp);
	else
		status = exec_execve(args[0], args, *envp, shell);
	return (status);
}

int	exec_cmd(t_cdll *node, t_shell *shell)
{
	char	**args;
	int		status;

	if (!node || !shell)
		return (0);
	status = 0;
	args = exec_args(node, shell);
	if (!args)
		return (0);
	if (!ft_strncmp(args[0], "exit", 4) && ft_strlen(args[0]) == 4)
		status = exit_cmd(args, shell->envp, shell);
	else if (!ft_strncmp(args[0], "cd", 2) && ft_strlen(args[0]) == 2)
		status = cd_cmd(args, &shell->envp, shell);
	else
		status = exec_cmd_func(args, &shell->envp, shell);
	free_str_tab(args);
	return (status);
}
