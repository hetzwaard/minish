/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tt_search.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 07:24:44 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 10:32:56 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	tt_inc_ptrs(char **pat_p, char **file_p)
{
	(*pat_p)++;
	(*file_p)++;
}

static char	*tt_find_subpattern(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *) big);
	while (big[i])
	{
		j = 0;
		while (big[j + i] == little[j] && big[j + i])
		{
			j++;
			if (j == len)
				return ((char *) big + i);
		}
		i++;
	}
	return (NULL);
}

static char	*tt_find_next_wildcard(char *pat_p)
{
	char	*next_wildcard;

	next_wildcard = ft_strchr(pat_p, '*');
	if (!next_wildcard)
		next_wildcard = pat_p + ft_strlen(pat_p);
	return (next_wildcard);
}

static int	tt_is_end_of_str(char **pat_p)
{
	while (**pat_p == '*')
		(*pat_p)++;
	if (**pat_p == '\0')
		return (1);
	return (0);
}

int	tt_is_match(char *pattern, char *filename)
{
	char	*next_wildcard;
	char	*pat_p;
	char	*file_p;

	pat_p = pattern;
	file_p = filename;
	while (*pat_p)
	{
		if (*pat_p == '*')
		{
			if (tt_is_end_of_str(&pat_p))
				return (1);
			next_wildcard = tt_find_next_wildcard(pat_p);
			file_p = tt_find_subpattern(file_p, pat_p, (next_wildcard - pat_p));
			if (!file_p)
				return (0);
			file_p += (next_wildcard - pat_p);
			pat_p = next_wildcard;
			continue ;
		}
		if (*file_p != *pat_p)
			return (0);
		tt_inc_ptrs(&pat_p, &file_p);
	}
	return (*file_p == '\0');
}
