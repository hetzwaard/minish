/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 08:49:52 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 10:29:53 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	unset_var(char *key, char ***envp)
{
	int		i;
	int		j;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], key, len) && ((*envp)[i][len] == '='
			|| (*envp)[i][len] == '\0'))
		{
			j = i;
			free((*envp)[i]);
			while ((*envp)[j])
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (-1);
}

int	unset_cmd(char **args, char ***envp)
{
	int		i;
	char	**key;
	char	*name;

	if (!envp || !*envp || !args)
		return (error_shell("unset", "invalid arguments"));
	i = 1;
	while (args[i])
	{
		if (is_valid_var_name(args[i]))
		{
			key = get_env_var_ptr(args[i], *envp);
			if (key)
			{
				name = cut_var_name(*key);
				if (!name)
					return (-1);
				unset_var(name, envp);
				free(name);
			}
		}
		i++;
	}
	return (0);
}
