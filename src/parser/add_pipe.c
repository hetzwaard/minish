/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_pipe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 16:06:41 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:39:40 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

t_cmd_table *new_node(void)
{
	t_cmd_table	*new_cmd_table;

	new_cmd_table = malloc(sizeof(t_cmd_table));
	if (!new_cmd_table)
		return (NULL);
	new_cmd_table->cmd = NULL;
	new_cmd_table->heredoc_delim = NULL;
	new_cmd_table->infile = NULL;
	new_cmd_table->outfile = NULL;
	new_cmd_table->append_flag = 0;
	new_cmd_table->infd = 0;
	new_cmd_table->outfd = 0;
	new_cmd_table->next = NULL;
	return (new_cmd_table);
}

int	add_pipe(t_parsing *p)
{
	if (p->token->type == PIPE)
	{
		p->cmd_table->next = new_node();
		if (!p->cmd_table->next)
		{
			p->parser_error = "malloc failure:";
			return (-1);
		}
		p->cmd_table = p->cmd_table->next;
	}
	return (0);
}