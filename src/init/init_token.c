/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_token.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/05 16:08:19 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:41:33 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

void	init_token(t_token *token, int i)
{
	token->end = 0;
	token->len = 0;
	token->quote_flag = '\0';
	token->start = i;
	token->type = WORD;
}