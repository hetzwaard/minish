/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 22:26:46 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 14:11:43 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*prompt(t_shell *shell)
{
	static int	flag;

	if (!flag)
	{
		ft_printf(CLOVER "\n"
			"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗\n"
			"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║\n"
			"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║\n"
			"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║\n"
			"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║\n"
			"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝\n" RESET "\n");
		flag = 1;
	}
	if (shell->exit_status != 0 && shell->exit_status != 130)
		return (ORANGE "☘️  MINISH " RED ">" RESET " ");
	return (CLOVER "🍀 MINISH > " RESET);
}

char	*cut_var_name(char *str)
{
	char	*name;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_substr(str, 0, i);
	if (!name)
		return (error_shell("cut_name", "ft_sustr failed"), NULL);
	return (name);
}

int	is_valid_var_name(char *str)
{
	if (!str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

char	**realloc_str_arr(char **tab, size_t new_size)
{
	char	**new_tab;
	size_t	i;

	if (new_size == 0)
		return (free_str_tab(tab), NULL);
	new_tab = (char **) malloc(sizeof(char *) * new_size);
	if (!new_tab)
		return (NULL);
	i = 0;
	if (tab)
	{
		while (tab[i] && i < new_size)
		{
			new_tab[i] = tab[i];
			i++;
		}
	}
	while (i < new_size)
	{
		new_tab[i] = NULL;
		i++;
	}
	free(tab);
	return (new_tab);
}

void	exit_shell(t_shell *shell)
{
	rl_clear_history();
	unlink(TEMP_FILE);
	free_shell(shell);
}
