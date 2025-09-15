/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tt_pid.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/15 08:00:00 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/09/15 08:00:00 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*tt_replace_pid(char *str, char *dol_p)
{
	char	*value;
	char	*remainder;
	char	*temp_str;
	char	*new_str;
	pid_t	pid;

	if (!str)
		return (NULL);
	remainder = dol_p + 2;
	pid = getpid();
	value = ft_itoa(pid);
	if (!value)
		return (error_shell("tt_replace_pid", "ft_itoa failed"), NULL);
	str[dol_p - str] = '\0';
	temp_str = ft_strjoin(str, value);
	free(value);
	if (!temp_str)
		return (error_shell("tt_replace_pid", "ft_strjoin failed"), NULL);
	new_str = ft_strjoin(temp_str, remainder);
	free(temp_str);
	if (!new_str)
		return (error_shell("tt_replace_pid", "ft_strjoin failed"), NULL);
	return (new_str);
}

char	*tt_replace_status(char *str, char *dol_p, char **envp, int ex_stat)
{
	char	*value;
	char	*remainder;
	char	*temp_str;
	char	*new_str;

	if (!str || !envp)
		return (NULL);
	remainder = dol_p + 2;
	if (g_signals != 0)
		value = ft_itoa(130);
	else
		value = ft_itoa(ex_stat);
	if (!value)
		return (error_shell("tt_replace_status", "ft_itoa failed"), NULL);
	str[dol_p - str] = '\0';
	temp_str = ft_strjoin(str, value);
	free(value);
	if (!temp_str)
		return (error_shell("tt_replace_status", "ft_strjoin failed"), NULL);
	new_str = ft_strjoin(temp_str, remainder);
	free(temp_str);
	if (!new_str)
		return (error_shell("tt_replace_status", "ft_strjoin failed"), NULL);
	return (new_str);
}

static char	*tt_var_join(char *a, char *b, char *c)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(a, b);
	if (!tmp)
		return (error_shell("tt_var_join", "ft_strjoin failed"), NULL);
	res = ft_strjoin(tmp, c);
	free(tmp);
	if (!res)
		return (error_shell("tt_var_join", "ft_strjoin failed"), NULL);
	return (res);
}

char	*tt_replace_var(char *str, char *dol_p, char **envp)
{
	char	*var;
	char	*value;
	char	*rest;
	char	*res;

	if (!str || !envp)
		return (NULL);
	rest = get_var_name_end(dol_p + 1);
	if (rest == dol_p + 1)
		return (ft_strdup(str));
	var = ft_substr(str, dol_p - str + 1, (rest - str - (dol_p - str)) - 1);
	if (!var)
		return (error_shell("tt_replace_var", "ft_substr failed"), NULL);
	value = get_env_value(var, envp);
	if (!value)
		value = "";
	free(var);
	str[dol_p - str] = '\0';
	res = tt_var_join(str, value, rest);
	if (!res)
		return (NULL);
	return (res);
}
