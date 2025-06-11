/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_envp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 17:06:41 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:41:57 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

static t_envp	*create_node(char *value)
{
	t_envp	*new_node;

	new_node = malloc(sizeof(t_envp));
	if (new_node == NULL)
		return(NULL);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return(new_node);
}

void get_envp(t_minish *minish, char *envp[])
{
	int	i;
	t_envp *head = NULL;
	t_envp *current = NULL;
	t_envp *previous = NULL;
	
	i = 0;
	head = create_node(envp[i]);
	if (head == NULL)
		error_and_exit("malloc failure\n", minish);
	i++;
	previous = head;
	while(envp[i])
	{
		current = create_node(envp[i]);
		if (current == NULL)
			error_and_exit("malloc failure_1\n", minish);
		previous->next = current;
		previous = current;
		i++;
	}
	minish->envp = head;
}
