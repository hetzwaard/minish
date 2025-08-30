/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_execve.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 09:40:23 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/30 12:58:10 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*exec_find_path_in_path(char *cmd, char **path_split)
{
	int		i;
	char	*exec_path;
	char	*tmp;

	i = 0;
	while (path_split[i])
	{
		tmp = ft_strjoin(path_split[i], "/");
		if (!tmp)
			return (error_shell(cmd, "ft_strjoin failed"), NULL);
		exec_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!exec_path)
			return (error_shell(cmd, "ft_strjoin failed"), NULL);
		if (!access(exec_path, F_OK))
			return (exec_path);
		free(exec_path);
		i++;
	}
	return (NULL);
}

static char	*exec_find_exec_pathj(char *cmd, char **envp)
{
	char	*path;
	char	**path_split;
	char	*exec_path;

	path = get_env_value("PATH", envp);
	if (!path)
		return (NULL);
	path_split = ft_split(path, ':');
	if (!path_split)
		return (error_shell(path, "ft_split failed"), NULL);
	exec_path = exec_find_path_in_path(cmd, path_split);
	free_str_tab(path_split);
	return (exec_path);
}

static void	exec_child_proc(char *path, char **args, t_shell *shell)
{
	sig_child();
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	if (execve(path, args, shell->envp) == -1)
		error_perror(path, "exec_ve failed");
	free(path);
	exit(-1);
}

static int	exec_execve_cmd(char *path, char **args, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (error_perror(path, "fork failed"), -1);
	if (pid == 0)
		exec_child_proc(path, args, shell);
	return (sig_execve(pid, path));
}

int	exec_execve(char *cmd, char **args, char **envp, t_shell *shell)
{
	char	*path;
	int		ret;

	if (!cmd || !args || !envp)
		return (error_shell("exec_execve", "invalid arguments"));
	if (ft_strchr(cmd, '/'))
	{
		path = ft_strdup(cmd);
		if (!path)
			return (error_shell(cmd, "ft_strdup failed"));
		if (access(path, F_OK))
			return (free(path), error_shell(cmd,
					"No such file or directory"), -1);
	}
	else
		path = exec_find_exec_pathj(cmd, envp);
	if (!path)
		return (error_execve(cmd), 127);
	if (access(path, X_OK))
		return (free(path), error_shell(cmd, "permission denied"), 127);
	ret = exec_execve_cmd(path, args, shell);
	free(path);
	return (ret);
}
