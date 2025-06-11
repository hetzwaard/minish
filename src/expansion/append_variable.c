/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   append_variable.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 13:08:08 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/10 21:43:31 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

static char	*get_variable_name(char *input, char quote_flag, int i)
{
	char	*variable_name;
	int		j;

	j = 0;
	i = i + 1;
	while(input[i + j]
		&& (ft_isalnum(input[i + j])
			|| input[i + j] == '_'))
	{
		if (input[i + j] == quote_flag)
			break;
		j++;
	}
	variable_name = ft_substr(input, i, j);
	if (variable_name == NULL)
		return (NULL);
	return (variable_name);
}

static int	variable_located(t_expansion *expan, t_envp *head)
{
	if (ft_strncmp(head->value, expan->var_name, expan->var_name_len) == 0)
		return (0);
	return (1);
}

static int expand_variable(char *envp_value, t_expansion *expan)
{
	expan->var_expanded = ft_substr(envp_value, expan->var_name_len + 1, \
		ft_strlen(envp_value) - expan->var_name_len - 1);
	if (!expan->var_expanded)
		return (-1);
	return(0);
}

void	print_envp(t_envp *envp)
{
	t_envp *head;
	
	head = envp;
	while (head)
	{
		printf("%s\n", head->value);
		head = head->next;
	}
}

int	append_variable(t_expansion *expan, char *input, int *i)
{
	t_envp	*head;
	char	*temp;
	
	expan->var_name = get_variable_name(input, expan->quote_flag, *i);
	if (expan->var_name == NULL)
		return (-1);
	expan->var_name_len = ft_strlen(expan->var_name);
	head = expan->envp_copy;
	//print_envp(head);
	while (head)
	{
		if (variable_located(expan, head) == 0)
		{
			if (expand_variable(head->value, expan) == -1)
				return (-1);
			break ;
		}
		head = head->next;
	}
	if(expan->var_expanded == NULL)
		expan->var_expanded = ft_strdup("");
	if (!expan->var_expanded)
		return (-1);
	temp = ft_strjoin(expan->expanded_input, expan->var_expanded);
	if (temp == NULL)
		return (-1);
	free(expan->expanded_input);
	expan->expanded_input = temp;
	(*i) += expan->var_name_len;
	return (0);
}
