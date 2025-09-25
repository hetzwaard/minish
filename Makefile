# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iinclude -Iinclude/libft/include
LIBS = -Linclude/libft -lft

# Directories
SRCDIR = src
OBJDIR = objects
INCDIR = include
LIBFTDIR = include/libft
LIBFT = $(LIBFTDIR)/libft.a

# Find all .c files in src and subdirectories
SRCS =	$(SRCDIR)/main.c \
		$(SRCDIR)/cdll/cdll_create.c \
		$(SRCDIR)/cdll/cdll_heredoc.c \
		$(SRCDIR)/cdll/cdll_insert.c \
		$(SRCDIR)/cdll/cdll_remove.c \
		$(SRCDIR)/cdll/cdll_swap.c \
		$(SRCDIR)/cdll/cdll_utils.c \
		$(SRCDIR)/env/env_read.c \
		$(SRCDIR)/env/env_write.c \
		$(SRCDIR)/exec/builtins/cd.c \
		$(SRCDIR)/exec/builtins/echo.c \
		$(SRCDIR)/exec/builtins/env.c \
		$(SRCDIR)/exec/builtins/exit.c \
		$(SRCDIR)/exec/builtins/export.c \
		$(SRCDIR)/exec/builtins/pwd.c \
		$(SRCDIR)/exec/builtins/unset.c \
		$(SRCDIR)/exec/ops/paranthesis.c \
		$(SRCDIR)/exec/ops/pipex.c \
		$(SRCDIR)/exec/ops/redir_heredoc.c \
		$(SRCDIR)/exec/ops/redir_in.c \
		$(SRCDIR)/exec/ops/redir_out.c \
		$(SRCDIR)/exec/exec_args.c \
		$(SRCDIR)/exec/exec_cmd.c \
		$(SRCDIR)/exec/exec_execve.c \
		$(SRCDIR)/exec/exec_filename.c \
		$(SRCDIR)/exec/exec_leaf.c \
		$(SRCDIR)/exec/exec_tree.c \
		$(SRCDIR)/init/init_heredoc.c \
		$(SRCDIR)/init/init_shell.c \
		$(SRCDIR)/parse/token/token_kind.c \
		$(SRCDIR)/parse/token/token_misc.c \
		$(SRCDIR)/parse/token/token_parse.c \
		$(SRCDIR)/parse/token/token_redir.c \
		$(SRCDIR)/parse/token/token_spec.c \
		$(SRCDIR)/parse/tt/tt_dirlist.c \
		$(SRCDIR)/parse/tt/tt_dollar.c \
		$(SRCDIR)/parse/tt/tt_filenames.c \
		$(SRCDIR)/parse/tt/tt_replace.c \
		$(SRCDIR)/parse/tt/tt_search.c \
		$(SRCDIR)/parse/tt/tt_wildcard.c \
		$(SRCDIR)/parse/lexer.c \
		$(SRCDIR)/parse/parser.c \
		$(SRCDIR)/parse/tree.c \
		$(SRCDIR)/sig/sig_execve.c \
		$(SRCDIR)/sig/sig_heredoc.c \
		$(SRCDIR)/sig/sig_pipex.c \
		$(SRCDIR)/sig/sig_setup.c \
		$(SRCDIR)/sig/sig_sigint.c \
		$(SRCDIR)/utils/error/error_execve.c \
		$(SRCDIR)/utils/error/error_exit.c \
		$(SRCDIR)/utils/error/error_open.c \
		$(SRCDIR)/utils/error/error_parenthesis.c \
		$(SRCDIR)/utils/error/error_perror.c \
		$(SRCDIR)/utils/error/error_quote.c \
		$(SRCDIR)/utils/error/error_shell.c \
		$(SRCDIR)/utils/error/error_token.c \
		$(SRCDIR)/utils/error/error_warning.c \
		$(SRCDIR)/utils/free/free_cmd_line.c \
		$(SRCDIR)/utils/free/free_delim.c \
		$(SRCDIR)/utils/free/free_shell.c \
		$(SRCDIR)/utils/free/free_str_tab.c \
		$(SRCDIR)/utils/free/free_strings.c \
		$(SRCDIR)/utils/free/free_tree.c \
		$(SRCDIR)/utils/utils.c \

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Output executable
NAME = minishell

# Colors for output
CLOVER   = \033[38;2;120;200;80m
ORANGE  = \033[38;5;214m
GRAY    = \033[0;90m

# Rules
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo "$(GRAY)building minishell..."
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBS) -o $(NAME) -lreadline
	@echo "$(CLOVER)$(NAME) has been created successfully."

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(GRAY)building libft..."
	@make -C $(LIBFTDIR) > /dev/null
	@echo "$(CLOVER)libft has been created successfully."

clean:
	@echo "$(ORANGE)cleaning object files..."
	@rm -rf $(OBJDIR)
	@make -C $(LIBFTDIR) clean > /dev/null
	@echo "$(ORANGE)objects have been removed."

fclean: clean
	@echo "$(ORANGE)removing $(NAME)..."
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean > /dev/null
	@echo "$(ORANGE)$(NAME) has been removed."

re: fclean all

.PHONY: all clean fclean re
