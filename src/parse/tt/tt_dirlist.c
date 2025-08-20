/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tt_dirlist.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 07:30:50 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 07:31:55 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	tt_dirlist_copy(char **file_array, DIR *dir, size_t len, int mode)
{
	struct dirent	*entry;
	size_t			i;

	i = 0;
	while (i < len)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		else
		{
			if (entry->d_name[0] == '.' && mode == NO_HIDDEN)
				continue ;
			file_array[i] = ft_strdup(entry->d_name);
			if (!file_array[i])
			{
				error_perror("copy_files_in_dir", "ft_strdup failed");
				break ;
			}
		}
		i++;
	}
	file_array[i] = NULL;
}

static size_t	tt_dirlist_count(char *dirpath, int mode)
{
	DIR				*dir;
	size_t			size;
	struct dirent	*entry;

	dir = opendir(dirpath);
	size = 0;
	if (!dir)
		return (error_perror("tt_dirlist_count", "opendir failed"), size);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (mode == NO_HIDDEN && entry->d_name[0] != '.')
			size++;
		else
			size++;
	}
	if (closedir(dir) == -1)
		error_perror("tt_dirlist_count", "closedir failed");
	return (size);
}

char	**tt_dirlist(char *path, int mode)
{
	char			**file_array;
	DIR				*dir;
	size_t			len;

	len = tt_dirlist_count(path, mode);
	file_array = (char **) malloc(sizeof(char *) * (len + 1));
	if (!file_array)
		return (error_perror("tt_dirlist", "malloc failed"), NULL);
	file_array[len] = NULL;
	dir = opendir(path);
	if (!dir)
		return (error_perror("tt_dirlist", "opendir failed"), NULL);
	tt_dirlist_copy(file_array, dir, len, mode);
	if (closedir(dir) == -1)
		error_perror("tt_dirlist", "closedir failed");
	return (file_array);
}
