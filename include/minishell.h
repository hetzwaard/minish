/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 18:32:20 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/08/08 18:32:20 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// libraries
# include "libft/include/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// defines
# define SYMBOLS "<>|&;()'\""
# define WHITESPACES " \t\n\r\v\f"
# define NO_HIDDEN 0
# define W_HIDDEN 1
# define NO_PARENTHESIS 0
# define IN_PARENTHESIS 1
# define TEMP_FILE "/tmp/minishell_heredoc.tmp"

// color definitions
# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

// global variable
extern int			g_signals;

// structures and enums
typedef struct s_delim
{
	char			*str;
	int				is_litteral;
}					t_delim;

typedef struct s_token
{
	int				type;
	int				priority;
	int				space;
	char			*start;
	char			*end;
	int				str_is_malloc;
}					t_token;

typedef struct s_cdll
{
	void			*data;
	struct s_cdll	*prev;
	struct s_cdll	*next;
}					t_cdll;

typedef struct s_tree
{
	int				type;
	t_cdll			*list_node;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

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
}					t_shell;

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
}					t_token_type;

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
}					t_tree_type;

// init
t_shell				*init_shell(t_shell *shell, char **av, int ac, char **envp);
void				init_input(t_shell *gen);

// error
int					ft_error_msg(char *cmd, char *msg);

// free
void				exit_shell(t_shell *shell);
void				free_shell(t_shell *shell);

// env
size_t				get_env_count(char **envp);
char				**get_env_var_ptr(const char *var, char **envp);
char				*get_env_value(const char *var, char **envp);
int					cmp_env_keys(const char *s1, const char *s2);
char				*get_var_name_end(char *ptr);
char				**realloc_env(char ***envp, char *new_entry);
int					create_env(const char *key, char sep, const char *value,
						char ***envp);
int					update_env(const char *key, char sep, const char *value,
						char ***envp);
char				**copy_env(char **envp);

// cdll
t_cdll				*cdll_create_node(void *data);
t_cdll				*cdll_add_front(t_cdll **head, void *data);
t_cdll				*cdll_add_back(t_cdll **head, void *data);
void				cdll_remove_node(t_cdll **head, t_cdll *node);
void				cdll_clear(t_cdll **head);
int					cdll_swap_nodes(t_cdll **head, t_cdll *node1,
						t_cdll *node2);
void				cdll_move_node(t_cdll **src, t_cdll **dst, t_cdll *node);
int					cdll_get_node_index(t_cdll *head, t_cdll *node);
t_cdll				*cdll_get_node_at(t_cdll *head, int position);
int					cdll_get_node_count(t_cdll *head);

#endif