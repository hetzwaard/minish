/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tt_filenames.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 07:23:55 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 07:29:20 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**tt_filenames(char *arg, char **file_array)
{
	char	**matching_files;
	size_t	count;

	matching_files = NULL;
	count = 0;
	while (*file_array)
	{
		if (tt_is_match(arg, *file_array))
		{
			count++;
			matching_files = realloc_str_arr(matching_files, count + 1);
			if (!matching_files)
				return (error_shell("extract_matching_filenames",
						"realloc_str_arr failed"), NULL);
			matching_files[count - 1] = ft_strdup(*file_array);
			matching_files[count] = NULL;
		}
		file_array++;
	}
	return (matching_files);
}
