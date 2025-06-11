/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_parsing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/05 16:08:41 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:41:29 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

int init_parsing(t_parsing *p)
{
	p->cmd_table = ft_calloc(1, sizeof(t_cmd_table));
	if (!p->cmd_table)
		return (-1);
	p->head	= p->cmd_table;
	p->current = p->cmd_table;
	p->index = 0;
	p->temp_file = "/tmp/minishell_heredoc";
	p->parser_error = NULL;
	p->token = ft_calloc(1, sizeof(t_token));
	if (!p->token)
		return (-1);
	p->previous_token = ft_calloc(1, sizeof(t_token));
	if (!p->token)
		return (-1);
	return (0);
}
