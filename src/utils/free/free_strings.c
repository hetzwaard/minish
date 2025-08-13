/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_strings.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/09 02:56:59 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/09 02:57:07 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_strings(t_shell *shell)
{
	t_cdll	*current;
	t_token	*token;

	current = *shell->head;
	while (1)
	{
		token = (t_token *) current->data;
		if (token->str_is_malloc)
		{
			free(token->start);
			token->start = NULL;
			token->str_is_malloc = 0;
		}
		current = current->next;
		if (current == *shell->head)
			break ;
	}
}
