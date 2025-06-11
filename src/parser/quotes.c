/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 17:16:19 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:39:53 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

int purge_quotes(t_parsing *p, char **str)
{
	char	quote_flag;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote_flag = 0;
	temp = malloc (sizeof(char) * (ft_strlen(*str) + 1));
	if (!temp)
	{
		p->parser_error = "malloc failure:";
		return (-1);
	}
	while ((*str)[i])
	{
		if (quote_flag == 0 && ((*str)[i] == '\'' || (*str)[i] == '\"'))
			quote_flag = (*str)[i];
		else if ((*str)[i] != quote_flag)
			temp[j++] = (*str)[i];
		i++;
	}
	temp[j] = '\0';
	free(*str);
	*str = temp;
	return (0);
}
