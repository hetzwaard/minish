/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minish.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 18:35:06 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/06/11 13:58:06 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"

static void		print_cmd_table(t_cmd_table *cmd_table)
{
	int i;

	printf("\n--- Parsed Command Table ---\n");
    while (cmd_table)
    {
        printf("Command:\n");
        if (cmd_table->cmd)
        {
            i = 0;
            while (cmd_table->cmd[i])
            {
                printf("  string[%d]: %s\n", i, cmd_table->cmd[i]);
                i++;
            }
        }
        else
            printf("  No command found.\n");

        if (cmd_table->infile)
            printf("  Input File: %s\n", cmd_table->infile);
        else
            printf("  Input File: None\n");

        if (cmd_table->outfile)
            printf("  Output File: %s\n", cmd_table->outfile);
        else
            printf("  Output File: None\n");
		if (cmd_table->append_flag == 0)
			printf(" Append_flag: %i\n", cmd_table->append_flag);
		else 
			printf("  Append_flag: 1\n");
			
        printf("  Append Mode: %s\n", cmd_table->heredoc_delim ? "Yes" : "No");

        if (cmd_table->heredoc_delim)
            printf("  Heredoc Delimiter: %s\n", cmd_table->heredoc_delim);
        else
            printf("  Heredoc Delimiter: None\n");

        printf("  Input FD: %d\n", cmd_table->infd);
        printf("  Output FD: %d\n", cmd_table->outfd);

        cmd_table = cmd_table->next;
        if (cmd_table)
            printf("\n--- Next Command ---\n");
    }
	printf("--- End of Command Table ---\n");
}
static int		has_syntax_error(const char *input)
{
	int		i;
	char	quote_flag;

	i = 0;
	quote_flag = '\0';
	while (input[i])
	{	
		if (quote_flag == '\0' && (input[i] == '\\' || input[i] == ';'))
			return (1);
		if (quote_flag == '\0' 
			&& (input[i] == '\'' || input[i] == '\"'))
			quote_flag = input[i];
		if (quote_flag == input[i] 
			&& (input[i] == '\'' || input[i] == '\"'))
			quote_flag = '\0';
		i++;
	}
	if (quote_flag != '\0')
	{
		ft_putstr_fd("minish: syntax error: unclosed quote\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static void		run_minish(t_minish *minish)
{
	while (1)
	{
		minish->input = readline(CLOVER"🍀 minish$>"RST);
		if (!minish->input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break;
		}
		if (has_syntax_error(minish->input) == 1)
		{
			free(minish->input);
			continue ;
		}
		if (minish->input[0])
			add_history(minish->input);
		if (parser(minish) == -1)
		{
			free(minish->input);
			continue ;
		}
		print_cmd_table(minish->cmd_table);
		//execution(minish);
		free(minish->input);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_minish minish;

	(void)argv;
	if (argc > 1)
	{
		// TODO return simple error to 2.
	}
	//handle_signals();
	init_minish(&minish, envp);
	run_minish(&minish);
	rl_clear_history();
	//exit_minish();
}