/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tt_dollar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 07:10:36 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 09:58:55 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*tt_replace_var(char *str, char *dol_p, char **envp)
{
	char			*var;
	char			*value;
	char			*rest;
	char			*temp_str;
	char			*new_str;

	if (!str || !envp)
		return (NULL);
	rest = get_var_name_end(dol_p + 1);
	var = ft_substr(str, dol_p - str + 1, (rest - str - (dol_p - str)) - 1);
	if (!var)
		return (error_shell("tt_replace_var", "ft_strdup failed"), NULL);
	value = get_env_value(var, envp);
	if (!value)
		value = "";
	free(var);
	str[dol_p - str] = '\0';
	temp_str = ft_strjoin(str, value);
	if (!temp_str)
		return (error_shell("tt_replace_var", "ft_strjoin failed"), NULL);
	new_str = ft_strjoin(temp_str, rest);
	free(temp_str);
	if (!new_str)
		return (error_shell("tt_replace_var", "ft_strjoin failed"), NULL);
	return (new_str);
}

static char	*tt_replace_status(char *str, char *dol_p, char **envp, int ex_stat)
{
	char	*value;
	char	*remainder;
	char	*temp_str;
	char	*new_str;

	if (!str || !envp)
		return (NULL);
	remainder = dol_p + 2;
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

static char	*tt_replace_loop(char *res, char *ptr, char *str, t_shell *shell)
{
	int	i;

	i = 0;
	while (1)
	{
		ptr = ft_strchr(res + i, '$');
		if (!ptr)
			break ;
		if (*(ptr + 1) == '.')
		{
			i++;
			continue ;
		}
		str = res;
		if (*(ptr + 1) == '?')
			res = tt_replace_status(str, ptr, shell->envp, shell->exit_status);
		else
			res = tt_replace_var(str, ptr, shell->envp);
		free(str);
		if (!res)
			return (NULL);
	}
	return (res);
}

char	*tt_expand(char *str, t_shell *shell)
{
	char	*ptr;
	char	*res;

	if (!str || !shell || !shell->envp)
		return (error_shell("tt_expand", "invalid arg"), NULL);
	ptr = NULL;
	res = ft_strdup(str);
	if (!res)
		return (error_shell("tt_expand", "ft_strdup failed"), NULL);
	if (res[0] == '~' && (res[1] == '/' || res[1] == '\0'))
	{
		ptr = res;
		res = ft_strjoin(shell->home, ptr + 1);
		free(ptr);
		if (!res)
			return (error_shell("tt_expand",
					"ft_strjoin failed"), NULL);
	}
	return (tt_replace_loop(res, ptr, str, shell));
}

char	*tt_dollar(t_token *token, t_shell *shell)
{
	char	*str;

	if (!token || !shell)
		return (error_shell("tt_dollar", "invalid arg"), NULL);
	if (token->type < TOKEN_STRING || token->type > TOKEN_LITTERAL)
		return (error_shell("tt_dollar", "invalid token type"), NULL);
	if (token->type != TOKEN_STRING && token->type != TOKEN_WORD)
	{
		str = ft_strdup(token->start);
		if (!str)
			return (error_shell("tt_dollar", "ft_strdup failed"), NULL);
	}
	else
		str = tt_expand(token->start, shell);
	if (!str)
		return (NULL);
	return (str);
}
