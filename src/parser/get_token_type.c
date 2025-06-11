/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_token_type.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 12:41:02 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:39:43 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

t_token_type get_token_type(char * input, t_token *token)
{
	if (ft_strncmp(&input[token->start], "<", token->len) == 0)
		return (RE_IN);
	else if (ft_strncmp(&input[token->start], ">", token->len) == 0)
		return (RE_OUT);
	else if (ft_strncmp(&input[token->start], ">>", token->len) == 0)
		return (RE_APPEND);
	else if (ft_strncmp(&input[token->start], "<<", token->len) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(&input[token->start], "|", token->len) == 0)
		return (PIPE);
	else 
		return (WORD);
}