/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 16:16:25 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:42:08 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

void	get_pwd(t_minish *minish)
{
	t_envp	*head;
	
	head = minish->envp;
	while (head != NULL)
	{
		//printf("hello\n");
		if (ft_strncmp(head->value, "PWD=", 4) == 0)
		{
			minish->pwd = ft_strdup(head->value + 4);
			if (minish->pwd == NULL)
				error_and_exit("malloc failure\n", minish);
			break;
		}
		head = head->next;
	}
}