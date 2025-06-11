/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_command.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 12:42:12 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 22:04:34 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

static  void create_new_command_array(t_parsing *p, char *command)
{
	p->cmd_table->cmd = malloc(sizeof(char *) * 2);
	if (!p->cmd_table->cmd)
		return ;
	p->cmd_table->cmd[0] = ft_strdup(command);
	if (!p->cmd_table->cmd[0])
	{
		p->parser_error = "malloc error:";
		free(p->cmd_table->cmd);
		return ;
	}
	p->cmd_table->cmd[1] = NULL;

}

static int add_to_command_table(t_parsing *p, char *command)
{
	char	**new_array;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (p->cmd_table->cmd[i])
		i++;
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		return (-1);
	while (j < i)
	{
		new_array[j] = ft_strdup(p->cmd_table->cmd[j]);
		j++;
	}
	new_array[i] = ft_strdup(command);
	new_array[i + 1] = NULL;
	ft_free_arr(p->cmd_table->cmd);
	p->cmd_table->cmd = new_array;
	return (0);
}

int	add_command(t_parsing *p, char *input)
{
	char *command_token;
	
	if (p->token->type == WORD)
	{
		command_token = ft_substr(input, p->token->start, p->token->len);
		if (!command_token)
		{
			p->parser_error = "malloc error:";
			return (-1);
		}
		if (purge_quotes(p, &command_token) == -1)
			return (free(command_token), -1);
		if (!p->cmd_table->cmd)
		{
			create_new_command_array(p, command_token);
			if (!p->cmd_table->cmd)
				return (free(command_token), -1);
			return (0);
		}
		else if (add_to_command_table(p, command_token) == -1)
			return (free(command_token), -1);
		free(command_token);
	}
	return (0);
}


	//create substring of the token from the input.
	// remove the unnquotes from the input
	// if !new command return -1)
	// if the command table has not been allocated.then malloc.
		// set the new_command string to the command table[0].
		// set command[1] to NULL.
		// free anything than needs to be free'd.