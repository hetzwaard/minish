/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 23:55:21 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/08 23:55:21 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parser(t_cdll **head, t_shell *shell, int state)
{
	if (!head || !*head)
		return (258);
	//return (check_nodes(*head, shell, state));
}