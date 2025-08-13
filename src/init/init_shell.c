/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_shell.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 19:49:32 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/08 19:49:32 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_input(t_shell *gen)
{
	gen->in_start = gen->input;
	gen->in_end = gen->input + ft_strlen(gen->input);
	gen->input_cpy = ft_strdup(gen->input);
	gen->head = tokenize(gen->input);
}

static void	init_home(t_shell *shell)
{
	char	*home;

	home = get_env_value("HOME", shell->envp);
	if (home)
	{
		shell->home = ft_strdup(home);
		if (!shell->home)
			error_shell("init_home", "ft_strdup failed");
	}
	else
		shell->home = ft_strdup(shell->pwd);
}

static void	init_pwd(t_shell *shell)
{
	char	pwd(PATH_MAX);

	unset_one_env_var("OLDPWD", &shell->envp);
	if (!getcwd(pwd, sizeof(pwd)))
		error_shell("init_pwd", "getcwd failed");
	shell->pwd = ft_strdup(pwd);
	if (!shell->pwd)
	{
		error_shell("init_pwd", "ft_strdup failed");
		free_shell(shell);
		exit (1);
	}
}

static int	init_shlvl(char **envp)
{
	char	*shlvl;
	char	*new_shlvl;
	int		i;

	shlvl = get_env_value("SHLVL", *envp);
	if (!shlvl)
		i = 0;
	else
		i = ft_atoi(shlvl);
	new_shlvl = ft_itoa(i + 1);
	if (!new_shlvl)
		return (error_shell("change_shlvl", "ft_itoa failed"));
	update_env_var("SHLVL", '=', new_shlvl, envp);
	free(new_shlvl);
	return (0);
}

t_shell	*init_shell(t_shell *shell, char **av, int ac, char **envp)
{
	(void)ac;
	(void)av;
	shell = (t_shell *) malloc(sizeof(t_shell));
	if (!shell)
	{
		error_shell("init_shell", "malloc failed");
		exit (1);
	}
	ft_memset(shell, 0, sizeof(t_shell));
	shell->envp = copy_env(envp);
	if (!shell->envp)
	{
		error_shell("init_shell", "failed to copy envp");
		free_shell(shell);
		exit (1);
	}
	init_shlvl(&shell->envp);
	init_pwd(shell);
	init_home(shell);
	return (shell);
}
