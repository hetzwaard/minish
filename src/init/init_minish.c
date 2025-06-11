/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_minish.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/10 21:42:31 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/06/11 13:53:40 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

// static void	print_envp(t_minish *minish)
// {
// 	t_envp *head;
	
// 	head = minish->envp;
// 	while (head)
// 	{
// 		printf("%s\n", head->value);
// 		head = head->next;
// 	}
// }

void	init_minish(t_minish *minish, char *envp[])
{
	// int i;

	// i = 0;
	init_banner();
	get_envp(minish, envp);
	//print_envp(minish);
	get_pwd(minish);
	minish->main_process_pid = getpid();
	minish->input = NULL;
	minish->exit_code = 0;
	minish->cmd_table = ft_calloc(1, sizeof(t_cmd_table));
	if (minish->cmd_table == NULL)
		error_and_exit("malloc failure\n", minish);
}