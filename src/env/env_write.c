/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_write.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 20:33:39 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 08:42:53 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_realloc(char ***envp, char *new_entry)
{
	char	**new_envp;
	size_t	i;

	if (!envp)
		return (error_shell("env_realloc", "invalid arguments"), NULL);
	new_envp = (char **) malloc(sizeof(char *) * (get_env_count(*envp) + 2));
	if (!new_envp)
		return (error_shell("env_copy", "malloc failed"), NULL);
	i = 0;
	while ((*envp)[i])
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		if (!new_envp[i])
		{
			ft_free_arr(new_envp);
			return (error_shell("env_copy", "ft_strdup failed"), NULL);
		}
		i++;
	}
	new_envp[i] = ft_strdup(new_entry);
	new_envp[i + 1] = NULL;
	ft_free_arr(*envp);
	*envp = new_envp;
	return (*envp);
}

int	env_create(const char *key, char sep, const char *value, char ***envp)
{
	char	*new_entry;
	char	*temp;

	if (!envp || !key)
		return (error_shell("env_create", "invalid arguments"));
	if (sep != '=')
		new_entry = ft_strdup(key);
	else
	{
		new_entry = ft_strjoin(key, "=");
		if (value)
		{
			temp = new_entry;
			new_entry = ft_strjoin(new_entry, value);
			free(temp);
		}
	}
	if (!new_entry)
		return (error_shell("env_create", "strjoin or strdup failed"));
	if (!env_realloc(envp, new_entry))
		return (free(new_entry), -1);
	free(new_entry);
	return (0);
}

int	env_update(const char *key, char sep, const char *value, char ***envp)
{
	char	**var;
	char	*temp;
	char	*new_entry;

	if (!envp || !key)
		return (error_shell("env_update", "invalid arguments"));
	var = get_env_var_ptr(key, *envp);
	if (!var)
		return (env_create(key, sep, value, envp));
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (error_shell("env_update", "strjoin failed"));
	if (!value)
		new_entry = ft_strdup(temp);
	else
		new_entry = ft_strjoin(temp, value);
	free(temp);
	if (!new_entry)
		return (error_shell("env_update", "strjoin failed"));
	free(*var);
	*var = new_entry;
	return (0);
}

char	**env_copy(char **envp)
{
	char	**new_envp;
	size_t	size;
	size_t	i;

	if (!envp)
		return (error_shell("env_copy", "invalid arguemnts"), NULL);
	size = get_env_count(envp);
	new_envp = malloc(sizeof(char *) * (size + 1));
	if (!new_envp)
		return (error_shell("env_copy", "malloc fialed"), NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			ft_free_arr(new_envp);
			return (error_shell("env_copy", "ft_strdup failed"), NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
