/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 21:47:50 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/08 21:47:50 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	get_env_count(char **envp)
{
	size_t	i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**get_env_var_ptr(const char *var, char **envp)
{
	size_t	len;
	int		i;

	if (!var || !envp)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len) && (envp[i][len] == '='
			|| envp[i][len] == '\0'))
			return (&envp[i]);
		i++;
	}
	return (NULL);
}

char	*get_env_value(const char *var, char **envp)
{
	size_t	len;
	int		i;

	if (!var || !envp)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	cmp_env_keys(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 != '=' && *s2 != '=' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == '=' || *s2 == '=')
		return (*s1 - *s2);
	return (*s1 - *s2);
}

char	*get_var_name_end(char *ptr)
{
	if (!ptr)
		return (NULL);
	if (!ft_isalpha(*ptr) && *ptr != '_')
		return (ptr);
	while (ft_isalnum(*ptr) || *ptr == '_')
		ptr++;
	return (ptr);
}
