/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 08:49:44 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 10:29:43 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*export_next_lowest(char *var, char **envp)
{
	int		i;
	char	*temp;

	if (!envp)
		return (NULL);
	temp = NULL;
	i = 0;
	while (envp[i])
	{
		if ((!var || cmp_env_keys(envp[i], var) > 0)
			&& (!temp || cmp_env_keys(envp[i], temp) < 0))
		{
			temp = envp[i];
		}
		i++;
	}
	return (temp);
}

static void	export_print_chars(char *start, char *end)
{
	while (start < end)
	{
		ft_putchar_fd(*start, 1);
		start++;
	}
}

static int	export_print_env(char **envp)
{
	char	*var;
	char	*eq;
	char	*value;

	if (!envp)
		return (ft_printf("\n"), -1);
	var = NULL;
	while (1)
	{
		var = export_next_lowest(var, envp);
		if (!var)
			break ;
		ft_printf("declare -x ");
		eq = ft_strchr(var, '=');
		if (!eq)
			ft_printf("%s\n", var);
		else
		{
			value = eq + 1;
			export_print_chars(var, eq);
			ft_printf("=\"%s\"", value);
			ft_printf("\n");
		}
	}
	return (0);
}

static void	export_var(char *arg, char *name, char ***envp)
{
	char	*value;

	value = ft_strchr(arg, '=');
	if (!value)
		env_update(name, ' ', NULL, envp);
	else if (*(value + 1) == '\0')
		env_update(name, '=', NULL, envp);
	else
		env_update(name, '=', (value + 1), envp);
	free(name);
}

int	export_cmd(char **args, char ***envp)
{
	int		i;
	int		status;
	char	*name;

	if (!envp || !*envp || !args || !args[0])
		return (error_shell("export", "invalid arguments"));
	status = 0;
	if (!args || !args[1])
		return (export_print_env(*envp), status);
	i = 1;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
			status = error_quote("export", args[i]);
		else
		{
			name = cut_var_name(args[i]);
			if (!name)
				return (-1);
			export_var(args[i], name, envp);
		}
		args++;
	}
	return (status);
}
