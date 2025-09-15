/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tt_dollar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 07:10:36 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/09/08 08:14:42 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*tt_process_dollar(char *res, char *ptr, t_shell *shell)
{
	char	*str;
	char	*new_res;

	str = res;
	if (*(ptr + 1) == '$')
		new_res = tt_replace_pid(str, ptr);
	else if (*(ptr + 1) == '?')
		new_res = tt_replace_status(str, ptr, shell->envp, shell->exit_status);
	else
		new_res = tt_replace_var(str, ptr, shell->envp);
	free(str);
	return (new_res);
}

static char	*tt_replace_loop(char *res, char *ptr, t_shell *shell)
{
	int	i;
	int	pos;

	i = 0;
	while (1)
	{
		ptr = ft_strchr(res + i, '$');
		if (!ptr)
			break ;
		if (*(ptr + 1) == '.')
		{
			i = (ptr - res) + 1;
			continue ;
		}
		pos = ptr - res;
		res = tt_process_dollar(res, ptr, shell);
		if (!res)
			return (NULL);
		i = pos + 1;
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
			return (error_shell("tt_expand", "ft_strjoin failed"), NULL);
	}
	return (tt_replace_loop(res, ptr, shell));
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
