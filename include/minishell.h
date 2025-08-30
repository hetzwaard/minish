/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 18:32:20 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/14 14:12:05 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// libraries
# include "libft/include/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <linux/limits.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

// defines
# define SYMBOLS "<>|&;()'\""
# define WHITESPACES " \t\n\r\v\f"
# define NO_HIDDEN 0
# define W_HIDDEN 1
# define NO_PARENTHESIS 0
# define IN_PARENTHESIS 1
# define TEMP_FILE "/tmp/minishell_heredoc.tmp"

// signal mode defines
# define _POSIX_C_SOURCE 200809L
# define MAIN 1
# define HEREDOC 2
# define CHILD 3
# define PARENT 4
# define IGNORE 5

// color definitions
# define Y "\033[1;33m"
# define G "\033[1;32m"
# define C "\033[1;36m"
# define RED "\033[1;31m"
# define RESET "\033[0m"
# define ORANGE "\033[38;5;214m"
# define CLOVER "\033[38;2;120;200;80m"

// global variable
extern int	g_signals;

// structures and enums
typedef struct s_delim
{
	char	*str;
	int		is_litteral;
}		t_delim;

typedef struct s_token
{
	int		type;
	int		priority;
	int		space;
	char	*start;
	char	*end;
	int		str_is_malloc;
}		t_token;

typedef struct s_cdll
{
	void			*data;
	struct s_cdll	*prev;
	struct s_cdll	*next;
}		t_cdll;

typedef struct s_tree
{
	int					type;
	t_cdll				*list_node;
	struct s_tree		*left;
	struct s_tree		*right;
}		t_tree;

typedef struct s_shell
{
	char			*pwd;
	char			*home;
	char			*input;
	char			*in_start;
	char			*in_end;
	char			*input_cpy;
	char			**envp;
	t_cdll			**head;
	t_tree			*tree;
	int				exit_status;
	int				stdin_backup;
	int				stdout_backup;
	int				in_pipe;
}		t_shell;

typedef enum e_token_type
{
	NOTHING,
	TOKEN_PARENTHESIS,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_REDIR_IN,
	TOKEN_HEREDOC,
	TOKEN_SEMICOLON,
	TOKEN_STRING,
	TOKEN_WORD,
	TOKEN_LITTERAL,
	TOKEN_EOF,
	TOKEN_ERROR
}		t_token_type;

typedef enum e_tree_type
{
	TREE_NOTHING,
	TREE_PARENTHESIS,
	TREE_PIPE,
	TREE_AND,
	TREE_OR,
	TREE_SEMICOLON,
	TREE_COMMAND,
	TREE_ERROR
}		t_tree_type;

// builtins
void	exit_cmd(char **args, char **envp, t_shell *shell);
int		cd_cmd(char **args, char ***envp, t_shell *shell);
int		echo_cmd(char **args, char **envp);
int		env_cmd(char **args, char **envp);
int		export_cmd(char **args, char ***envp);
int		pwd_cmd(char **args, char **envp);
int		unset_cmd(char **args, char ***envp);
int		unset_var(char *key, char ***envp);

// init
void	init_input(t_shell *gen);
int		init_heredoc(t_cdll *node, t_shell *shell);
t_shell	*init_shell(t_shell *shell, int ac, char **av, char **envp);

// signals
void	sigint_prompt(int signum);
void	sigint_heredoc(int signum);
void	sig_set_signal(int mode);
void	sig_heredoc(void);
void	sig_setup(void);
int		sig_pipex(int left_pid, int right_pid);
void	sig_child(void);
int		sig_execve(pid_t pid, char *ctx);

// parser
t_cdll	**lexer_tokenize(char *input);
t_tree	*create_tree(t_cdll *left, t_cdll *right);

int		parser(t_cdll **head, t_shell *shell, int state);
int		parse_token(char **ps, char *es, char **q, char **eq);
int		parse_pipe(char **s);
int		parse_ampersand(char **s, char *es);
int		parse_semicolon(char **s);
int		parse_double_quote(char **s, char *es);
int		parse_single_quote(char **s, char *es);

// token
int		is_logical_operator(t_cdll *node);
int		is_parenthesis(t_cdll *node);
int		is_eof(t_cdll *node);
int		is_pipe(t_cdll *node);
int		is_tree_branch(t_cdll *node);
int		is_space(t_cdll *node);
int		is_filename(t_cdll *node);
int		is_and_or(t_cdll *node);
int		is_semicolon(t_cdll *node);
int		is_text(t_cdll *node);
int		is_redir(t_cdll *node);
int		is_heredoc(t_cdll *node);
int		is_redir_in(t_cdll *node);
int		is_redir_out(t_cdll *node);

// tt
char	**tt_dirlist(char *path, int mode);
char	*tt_expand(char *str, t_shell *shell);
char	*tt_dollar(t_token *token, t_shell *shell);
char	**tt_filenames(char *arg, char **file_array);
char	*tt_wildcard(char *arg, t_cdll *node, t_shell *shell);
int		tt_is_match(char *pattern, char *filename);

// error
void	error_execve(char *cmd);
void	error_exit(char *arg);
void	error_warning(char *delimiter, int n_line);
int		error_open(char *filename);
int		error_parenthesis(void);
int		error_perror(char *cmd, char *msg);
int		error_quote(char *cmd, char *msg);
int		error_shell(char *cmd, char *msg);
int		error_token(t_token *token);

// free
void	free_cmd_line(t_shell *shell);
void	free_delim(t_delim *delim);
void	free_shell(t_shell *shell);
void	free_str_tab(char **tab);
void	free_strings(t_shell *shell);
void	free_tree(t_tree *root);

// env
size_t	get_env_count(char **envp);
char	**get_env_var_ptr(const char *var, char **envp);
char	*get_env_value(const char *var, char **envp);
int		cmp_env_keys(const char *s1, const char *s2);
char	*get_var_name_end(char *ptr);
char	**env_realloc(char ***envp, char *new_entry);
int		env_create(const char *key, char sep, const char *value,
			char ***envp);
int		env_update(const char *key, char sep, const char *value,
			char ***envp);
char	**env_copy(char **envp);

// cdll
t_cdll	*cdll_create_node(void *data);
t_cdll	*cdll_next_heredoc(t_cdll *node);
t_cdll	*cdll_next_cmd(t_cdll *node);
t_cdll	*cdll_next_redir(t_cdll *node);
t_cdll	*cdll_add_front(t_cdll **head, void *data);
t_cdll	*cdll_add_back(t_cdll **head, void *data);
void	cdll_remove_node(t_cdll **head, t_cdll *node);
void	cdll_clear(t_cdll **head);
int		cdll_swap_nodes(t_cdll **head, t_cdll *node1,
			t_cdll *node2);
void	cdll_move_node(t_cdll **src, t_cdll **dst, t_cdll *node);
int		cdll_get_node_index(t_cdll *head, t_cdll *node);
t_cdll	*cdll_get_node_at(t_cdll *head, int position);
int		cdll_get_node_count(t_cdll *head);

// exec
int		parenthesis(t_tree *tree, t_shell *shell);
int		pipex(t_tree *tree, t_shell *shell);
int		redir_heredoc(void);
int		redir_in(t_cdll *node, t_shell *shell);
int		redir_out(t_cdll *node, t_shell *shell);

char	**exec_args(t_cdll *node, t_shell *shell);
char	*exec_filename(t_cdll *node, t_shell *shell);
int		exec_cmd(t_cdll *node, t_shell *shell);
int		exec_tree(t_tree *tree_node, t_shell *shell);
int		exec_execve(char *cmd, char **args, char **envp, t_shell *shell);
int		exec_leaf(t_cdll *node, t_shell *shell);

// utils
int		is_valid_var_name(char *str);
char	*prompt(t_shell *shell);
char	*cut_var_name(char *str);
char	**realloc_str_arr(char **tab, size_t new_size);
void	exit_shell(t_shell *shell);

#endif